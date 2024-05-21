#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "PlayerMarker/Enums/Enums.h"
#include "PlayerMarkerGameState.generated.h"



class APlayerMarkerPlayerState;



USTRUCT()
struct FPlayerInformation
{
	GENERATED_BODY()

	UPROPERTY()
	APlayerMarkerPlayerState* PlayerState;

	UPROPERTY()
	ETeam Team;
};

USTRUCT()
struct FSquad
{
	GENERATED_BODY()

	UPROPERTY()
	ETeam Team;

	UPROPERTY()
	ESquadName Name;

	UPROPERTY()
	TArray<APlayerMarkerPlayerState*> Members;
};



UCLASS()
class PLAYERMARKER_API APlayerMarkerGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	APlayerMarkerGameState();
	void InitializeSquads(ETeam Team);
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(Replicated)
	TArray<FPlayerInformation> Players;

	UPROPERTY(Replicated)
	TArray<FSquad> Squads;

	void AddPlayerToTeam(APlayerMarkerPlayerState* Player, ETeam Team);
	void AddPlayerToSquad(APlayerMarkerPlayerState* Player, ETeam Team, ESquadName SquadName);
	void RemovePlayerFromTeam(APlayerMarkerPlayerState* Player);
	void RemovePlayerFromSquad(APlayerMarkerPlayerState* Player);
	int32 GetTeamPlayerCount(ETeam Team);
};
