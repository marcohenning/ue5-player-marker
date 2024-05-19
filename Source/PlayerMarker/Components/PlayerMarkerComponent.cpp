#include "PlayerMarkerComponent.h"
#include "PlayerMarker/Widgets/PlayerMarkerWidget.h"
#include "PlayerMarker/Character/FirstPersonCharacter.h"



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
}
