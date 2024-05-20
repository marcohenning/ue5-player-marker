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
	if (PlayerMarkerWidget == nullptr) { return; }

	CalculateWidgetSize(LocallyControlledCharacter, OtherCharacter);
	PlayerMarkerWidget->SetPlayerName("ENEMY");
	PlayerMarkerWidget->SetPlayerNameColor(PlayerMarkerWidget->ColorEnemy);
}

void UPlayerMarkerComponent::HandleSameTeamDifferentSquad(AFirstPersonCharacter* 
	LocallyControlledCharacter, AFirstPersonCharacter* OtherCharacter)
{
	if (PlayerMarkerWidget == nullptr) { return; }

	CalculateWidgetSize(LocallyControlledCharacter, OtherCharacter);
	PlayerMarkerWidget->SetPlayerName("TEAM");
}

void UPlayerMarkerComponent::HandleSameTeamSameSquad(AFirstPersonCharacter* 
	LocallyControlledCharacter, AFirstPersonCharacter* OtherCharacter)
{
	if (PlayerMarkerWidget == nullptr) { return; }

	CalculateWidgetSize(LocallyControlledCharacter, OtherCharacter);
	PlayerMarkerWidget->SetPlayerName("SQUAD");
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

	/** Calculating render scale based on distance */
	float RenderScale;

	if (Distance <= MinDistance) { RenderScale = MaxRenderScale; }
	else if (Distance >= MaxDistance) { RenderScale = MinRenderScale; }
	else
	{
		RenderScale = FMath::Lerp(MaxRenderScale, MinRenderScale, Distance / MaxDistance);
		RenderScale = FMath::Clamp(RenderScale, MinRenderScale, MaxRenderScale);
	}

	PlayerMarkerWidget->SetRenderScale(FVector2D(RenderScale, RenderScale));
}
