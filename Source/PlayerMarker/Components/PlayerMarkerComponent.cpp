#include "PlayerMarkerComponent.h"
#include "Components/WidgetComponent.h"
#include "PlayerMarker/Widgets/PlayerMarkerWidget.h"
#include "PlayerMarker/Character/FirstPersonCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"



UPlayerMarkerComponent::UPlayerMarkerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UPlayerMarkerComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UPlayerMarkerComponent::UpdatePlayerMarker(AFirstPersonCharacter* 
	LocallyControlledCharacter, AFirstPersonCharacter* OtherCharacter)
{
	if (LocallyControlledCharacter == nullptr || OtherCharacter == nullptr) { return; }

	if (LocallyControlledCharacter->GetTeam() == OtherCharacter->GetTeam())
	{
		if (LocallyControlledCharacter->GetSquad() == OtherCharacter->GetSquad())
		{
			HandleSameTeamSameSquad(LocallyControlledCharacter, OtherCharacter);
		}
		else { HandleSameTeamDifferentSquad(LocallyControlledCharacter, OtherCharacter); }
	}
	else { HandleDifferentTeam(LocallyControlledCharacter, OtherCharacter); }
}

void UPlayerMarkerComponent::HandleDifferentTeam(AFirstPersonCharacter* 
	LocallyControlledCharacter, AFirstPersonCharacter* OtherCharacter)
{
	if (PlayerMarkerWidget) { PlayerMarkerWidget->SetUsername("ENEMY"); }
}

void UPlayerMarkerComponent::HandleSameTeamDifferentSquad(AFirstPersonCharacter* 
	LocallyControlledCharacter, AFirstPersonCharacter* OtherCharacter)
{
	if (PlayerMarkerWidget) { PlayerMarkerWidget->SetUsername("TEAM"); }
}

void UPlayerMarkerComponent::HandleSameTeamSameSquad(AFirstPersonCharacter* 
	LocallyControlledCharacter, AFirstPersonCharacter* OtherCharacter)
{
	if (PlayerMarkerWidget) { PlayerMarkerWidget->SetUsername("SQUAD"); }

	CalculateWidgetSize(LocallyControlledCharacter, OtherCharacter);
}

float UPlayerMarkerComponent::CalculateDistance(FVector Start, FVector End)
{
	return ((Start - End).Size() / 100.0f);
}

void UPlayerMarkerComponent::CalculateWidgetSize(AFirstPersonCharacter*
	LocallyControlledCharacter, AFirstPersonCharacter* OtherCharacter)
{
	/** Distance between the two characters in meters */
	float Distance = CalculateDistance(LocallyControlledCharacter->GetActorLocation(), 
		OtherCharacter->GetActorLocation());
	
	/** Calculating widget size not implemented yet */
	PlayerMarkerWidgetComponent->SetDrawSize(FVector2D(300.0f, 70.0f));
}

void UPlayerMarkerComponent::RotatePlayerMarkerToPlayerCamera()
{
	/** Get player marker widget location */
	const FVector PlayerMarkerLocation = PlayerMarkerWidgetComponent->GetComponentLocation();
	/** Get location of locally controlled character's camera */
	const FVector LocalCharacterCameraLocation = UGameplayStatics::
		GetPlayerCameraManager(GetWorld(), 0)->GetTransformComponent()->GetComponentLocation();

	/** Calculate rotation at which the widget faces the player's camera */
	const FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(
		PlayerMarkerLocation, LocalCharacterCameraLocation);

	/** Set player marker widget component rotation */
	PlayerMarkerWidgetComponent->SetWorldRotation(LookAtRotation);
}
