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



AFirstPersonCharacter::AFirstPersonCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	bUseControllerRotationYaw = true;

	/** Set up first person camera component */
	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCamera->SetupAttachment(GetMesh(), FName("head"));
	FirstPersonCamera->bUsePawnControlRotation = true;

	/** Set up player marker component */
	PlayerMarkerComponent = CreateDefaultSubobject<UPlayerMarkerComponent>(TEXT("PlayerMarkerComponent"));

	/** Set up player marker widget component */
	PlayerMarkerWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("PlayerMarkerWidgetComponent"));
	PlayerMarkerWidgetComponent->SetupAttachment(GetMesh(), FName("head"));
	PlayerMarkerWidgetComponent->SetWorldLocation(FVector(40.0f, 0.0f, 0.0f));
	PlayerMarkerWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);

	/** Set movement variables */
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	GetCharacterMovement()->AirControl = 1.f;

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
