#include "PlayerMarkerComponent.h"
#include "Components/WidgetComponent.h"
#include "PlayerMarker/Widgets/PlayerMarkerWidget.h"
#include "PlayerMarker/Character/FirstPersonCharacter.h"
#include "PlayerMarker/PlayerState/PlayerMarkerPlayerState.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "TimerManager.h"



UPlayerMarkerComponent::UPlayerMarkerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UPlayerMarkerComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UPlayerMarkerComponent, bSpotted);
}

bool UPlayerMarkerComponent::InitializePlayerMarkerComponent(AFirstPersonCharacter* 
	LocallyControlledCharacter, AFirstPersonCharacter* OtherCharacter)
{
	if (PlayerMarkerWidget == nullptr) { return false; }

	/** Get player state to access player name */
	APlayerMarkerPlayerState* OtherCharacterPlayerState = OtherCharacter->
		GetPlayerState<APlayerMarkerPlayerState>();

	/** Return false if player state is nullptr or team is none */
	if (OtherCharacterPlayerState == nullptr || LocallyControlledCharacter->GetTeam() == 
		ETeam::ET_TeamNone || OtherCharacter->GetTeam() == ETeam::ET_TeamNone)
	{
		return false;
	}

	PlayerMarkerWidget->SetPlayerName(OtherCharacterPlayerState->GetPlayerName());

	/** Distance is only shown on squad mates so initialize it with color squad */
	PlayerMarkerWidget->SetDistanceColor(PlayerMarkerWidget->ColorSquad);

	/** Compare team and squad of the two players and handle initializing the widget accordingly */
	if (LocallyControlledCharacter->GetTeam() == OtherCharacter->GetTeam())
	{
		if (LocallyControlledCharacter->GetSquad() == OtherCharacter->GetSquad())
		{
			PlayerMarkerWidget->SetPlayerNameColor(PlayerMarkerWidget->ColorSquad);
			PlayerMarkerWidget->SetHealthBarColor(PlayerMarkerWidget->ColorSquad,
				PlayerMarkerWidget->ColorSquadTransparent);
			PlayerMarkerWidget->SetIcon(PlayerMarkerWidget->IconSquad);
		}
		else
		{
			PlayerMarkerWidget->SetPlayerNameColor(PlayerMarkerWidget->ColorTeam);
			PlayerMarkerWidget->SetHealthBarColor(PlayerMarkerWidget->ColorTeam,
				PlayerMarkerWidget->ColorTeamTransparent);
			PlayerMarkerWidget->SetIcon(PlayerMarkerWidget->IconTeam);
		}
	}
	else
	{
		PlayerMarkerWidget->SetPlayerNameColor(PlayerMarkerWidget->ColorEnemy);
		PlayerMarkerWidget->SetHealthBarColor(PlayerMarkerWidget->ColorEnemy,
			PlayerMarkerWidget->ColorEnemyTransparent);
		PlayerMarkerWidget->SetIcon(PlayerMarkerWidget->IconEnemy);
	}

	bPlayerMarkerInitialized = true;
	return true;
}

void UPlayerMarkerComponent::UpdatePlayerMarker(AFirstPersonCharacter*
	LocallyControlledCharacter, AFirstPersonCharacter* OtherCharacter)
{
	if (LocallyControlledCharacter == nullptr || OtherCharacter == nullptr) { return; }

	/** Initialize player marker component */
	if (!bPlayerMarkerInitialized)
	{
		if (!InitializePlayerMarkerComponent(LocallyControlledCharacter, OtherCharacter)) { return; }
	}

	/** Compare team and squad of the two players and handle updating the widget accordingly */
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

	/** Debugging */
	if (bSpotted) { PlayerMarkerWidget->SetPlayerName("Spotted"); }
	else { PlayerMarkerWidget->SetPlayerName("Unspotted."); }
}

void UPlayerMarkerComponent::HandleSameTeamDifferentSquad(AFirstPersonCharacter* 
	LocallyControlledCharacter, AFirstPersonCharacter* OtherCharacter)
{
	if (PlayerMarkerWidget == nullptr) { return; }
}

void UPlayerMarkerComponent::HandleSameTeamSameSquad(AFirstPersonCharacter* 
	LocallyControlledCharacter, AFirstPersonCharacter* OtherCharacter)
{
	if (PlayerMarkerWidget == nullptr) { return; }

	/** Distance between the two characters in meters rounded to int32 */
	int32 Distance = FGenericPlatformMath::RoundToInt(CalculateDistance(
		LocallyControlledCharacter->GetActorLocation(), OtherCharacter->GetActorLocation()));

	/** Show health bar if close enough */
	if (Distance < SquadMaxHealthBarDistance)
	{
		PlayerMarkerWidget->ShowHealthBar();
		PlayerMarkerWidget->HideDistance();
	}
	/** Show distance instead of health bar if not close enough */
	else
	{
		PlayerMarkerWidget->SetDistance(Distance);
		PlayerMarkerWidget->ShowDistance();
		PlayerMarkerWidget->HideHealthBar();
	}
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

void UPlayerMarkerComponent::Spot()
{
	bSpotted = true;

	/** Clear existing timer */
	GetWorld()->GetTimerManager().ClearTimer(SpotTimer);

	/** Start timer to reset bSpotted flag after spot duration */
	GetWorld()->GetTimerManager().SetTimer(SpotTimer, this, &UPlayerMarkerComponent::SpotTimerFinished, SpotDuration);
}

void UPlayerMarkerComponent::SpotTimerFinished()
{
	bSpotted = false;
}
