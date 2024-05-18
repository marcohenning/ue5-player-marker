#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PlayerMarker/Enums/Enums.h"
#include "PlayerMarkerPlayerState.generated.h"



UCLASS()
class PLAYERMARKER_API APlayerMarkerPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(Replicated)
	ETeam Team = ETeam::ET_TeamNone;

	UPROPERTY(Replicated)
	ESquadName Squad = ESquadName::ESN_None;
};
