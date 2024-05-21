#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PlayerMarker/Enums/Enums.h"
#include "PlayerMarkerPlayerState.generated.h"


/**
* Custom player state storing player's team and squad.
*/
UCLASS()
class PLAYERMARKER_API APlayerMarkerPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	/** Player's team */
	UPROPERTY(Replicated)
	ETeam Team = ETeam::ET_TeamNone;

	/** Player's squad */
	UPROPERTY(Replicated)
	ESquadName Squad = ESquadName::ESN_None;
};
