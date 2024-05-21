#include "FirstPersonCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/WidgetComponent.h"
#include "PlayerMarker/Components/PlayerMarkerComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "PlayerMarker/PlayerState/PlayerMarkerPlayerState.h"
#include "PlayerMarker/PlayerController/PlayerMarkerPlayerController.h"
#include "PlayerMarker/Widgets/PlayerMarkerWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"



AFirstPersonCharacter::AFirstPersonCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	bUseControllerRotationYaw = true;

	/** Set up first person camera component */
	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCamera->SetupAttachment(GetMesh(), FName("head"));
	FirstPersonCamera->bUsePawnControlRotation = true;

	/** Set up player marker widget component */
	PlayerMarkerWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("PlayerMarkerWidgetComponent"));
	PlayerMarkerWidgetComponent->SetupAttachment(GetMesh(), FName("head"));
	PlayerMarkerWidgetComponent->SetWorldLocation(FVector(30.0f, 0.0f, 0.0f));
	PlayerMarkerWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	PlayerMarkerWidgetComponent->SetDrawAtDesiredSize(false);

	/** Set up player marker component */
	PlayerMarkerComponent = CreateDefaultSubobject<UPlayerMarkerComponent>(TEXT("PlayerMarkerComponent"));
	PlayerMarkerComponent->SetIsReplicated(true);
	PlayerMarkerComponent->PlayerMarkerWidgetComponent = PlayerMarkerWidgetComponent;

	/** Set movement variables */
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	GetCharacterMovement()->AirControl = 1.f;

	/** Let mesh block visibility channel to be able to hit character with line traces */
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);

	/** Set multiplayer replication frequencies */
	NetUpdateFrequency = 66.f;
	MinNetUpdateFrequency = 33.f;
}

void AFirstPersonCharacter::BeginPlay()
{
	Super::BeginPlay();

	/** Add input mapping context */
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<
			UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(MappingContextCharacter, 0);
		}
	}

	/** Get displayed player marker widget and set player maker component's member variable */
	PlayerMarkerComponent->PlayerMarkerWidget = Cast<UPlayerMarkerWidget>(
		PlayerMarkerWidgetComponent->GetUserWidgetObject());

	/** Add crosshair widget to the viewport */
	if (CrosshairWidgetClass)
	{
		CreateWidget<UUserWidget>(GetWorld(), CrosshairWidgetClass)->AddToViewport();
	}
}

void AFirstPersonCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/** Only update the player marker on not locally controlled players */
	if (IsLocallyControlled()) { return; }

	/** Initialize pointer to locally controlled character if nullptr */
	if (LocallyControlledCharacter == nullptr)
	{
		LocallyControlledCharacter = Cast<AFirstPersonCharacter>(UGameplayStatics::
			GetPlayerControllerFromID(this, 0)->GetCharacter());
	}

	/** Call update player marker function on player marker component */
	if (LocallyControlledCharacter && PlayerMarkerComponent)
	{
		PlayerMarkerComponent->UpdatePlayerMarker(LocallyControlledCharacter, this);
	}
}

void AFirstPersonCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	/** Set up input action bindings */
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AFirstPersonCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AFirstPersonCharacter::Look);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		EnhancedInputComponent->BindAction(SpotAction, ETriggerEvent::Started, this, &AFirstPersonCharacter::SpotButtonPressed);
	}
}

void AFirstPersonCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (GetController())
	{
		const FRotator Rotation = GetController()->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AFirstPersonCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookVector = Value.Get<FVector2D>();

	if (GetController())
	{
		AddControllerYawInput(LookVector.X);
		AddControllerPitchInput(LookVector.Y);
	}
}

void AFirstPersonCharacter::SpotButtonPressed()
{
	/** Get viewport center */
	FVector2D ViewportSize;
	if (GEngine->GameViewport) { GEngine->GameViewport->GetViewportSize(ViewportSize); }
	FVector2D ViewportCenter(ViewportSize.X / 2.0f, ViewportSize.Y / 2.0f);

	/** Convert viewport center from screen space to world space */
	FVector ViewportCenterWorldPosition;
	FVector ViewportCenterWorldDirection;
	bool bScreenToWorld = UGameplayStatics::DeprojectScreenToWorld(UGameplayStatics::GetPlayerController(
		this, 0), ViewportCenter, ViewportCenterWorldPosition, ViewportCenterWorldDirection);

	/** Request server to validate the spotting */
	if (bScreenToWorld) { ServerRequestSpot(ViewportCenterWorldPosition, ViewportCenterWorldDirection); }
}

void AFirstPersonCharacter::ServerRequestSpot_Implementation(FVector ViewportCenterWorldPosition, 
	FVector ViewportCenterWorldDirection)
{
	/** Start of the line trace offset by 1 meter to avoid hitting own mesh */
	FVector Start = ViewportCenterWorldPosition + ViewportCenterWorldDirection * 100.0f;
	/** End of the line trace 1000 meters from start */
	FVector End = Start + ViewportCenterWorldDirection * 100000.0f;

	/** Perform line trace */
	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_Visibility);
	DrawDebugLine(GetWorld(), Start, End, FColor(255, 0, 0), false, 5.0f, 0, 1.0f);

	/** Check if hit actor is of class AFirstPersonCharacter and spot them */
	if (HitResult.GetActor())
	{
		AFirstPersonCharacter* HitCharacter = Cast<AFirstPersonCharacter>(HitResult.GetActor());

		/** Spot only if the hit character is from the enemy team */
		if (HitCharacter && HitCharacter->GetTeam() != GetTeam())
		{
			HitCharacter->GetPlayerMarkerComponent()->Spot();
		}
	}
}

ETeam AFirstPersonCharacter::GetTeam()
{
	PlayerMarkerPlayerState = PlayerMarkerPlayerState == nullptr ? 
		GetPlayerState<APlayerMarkerPlayerState>() : PlayerMarkerPlayerState;

	if (PlayerMarkerPlayerState)
	{
		return PlayerMarkerPlayerState->Team;
	}

	return ETeam::ET_TeamNone;
}

ESquadName AFirstPersonCharacter::GetSquad()
{
	PlayerMarkerPlayerState = PlayerMarkerPlayerState == nullptr ?
		GetPlayerState<APlayerMarkerPlayerState>() : PlayerMarkerPlayerState;

	if (PlayerMarkerPlayerState)
	{
		return PlayerMarkerPlayerState->Squad;
	}

	return ESquadName::ESN_None;
}
