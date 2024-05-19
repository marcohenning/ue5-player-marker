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
	RotatePlayerMarkerToPlayerCamera();
}

void UPlayerMarkerComponent::HandleSameTeamDifferentSquad(AFirstPersonCharacter* 
	LocallyControlledCharacter, AFirstPersonCharacter* OtherCharacter)
{
	if (PlayerMarkerWidget) { PlayerMarkerWidget->SetUsername("TEAM"); }
	RotatePlayerMarkerToPlayerCamera();
}

void UPlayerMarkerComponent::HandleSameTeamSameSquad(AFirstPersonCharacter* 
	LocallyControlledCharacter, AFirstPersonCharacter* OtherCharacter)
{
	if (PlayerMarkerWidget) { PlayerMarkerWidget->SetUsername("SQUAD"); }
	RotatePlayerMarkerToPlayerCamera();
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
