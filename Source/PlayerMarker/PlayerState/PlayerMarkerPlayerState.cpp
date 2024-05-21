#include "PlayerMarkerPlayerState.h"
#include "Net/UnrealNetwork.h"


void APlayerMarkerPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	/** Register variables for replication */
	DOREPLIFETIME(APlayerMarkerPlayerState, Team);
	DOREPLIFETIME(APlayerMarkerPlayerState, Squad);
}
