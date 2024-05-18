#include "PlayerMarkerGameState.h"
#include "Net/UnrealNetwork.h"



APlayerMarkerGameState::APlayerMarkerGameState()
{

}

void APlayerMarkerGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APlayerMarkerGameState, Players);
	DOREPLIFETIME(APlayerMarkerGameState, Squads);
}

void APlayerMarkerGameState::OnRep_Players()
{

}

void APlayerMarkerGameState::OnRep_Squads()
{

}
