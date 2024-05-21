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


/**
* Custom game state handling teams and squads.
*/
UCLASS()
class PLAYERMARKER_API APlayerMarkerGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	APlayerMarkerGameState();
	void InitializeSquads(ETeam Team);
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	/** Array containing structs mapping players to their teams */
	UPROPERTY(Replicated)
	TArray<FPlayerInformation> Players;

	/** Array containing FSquad struct for each squad (initialized in constructor) */
	UPROPERTY(Replicated)
	TArray<FSquad> Squads;

	/**
	* Functions for adding and removing players from teams and squads
	*/
	void AddPlayerToTeam(APlayerMarkerPlayerState* Player, ETeam Team);
	void AddPlayerToSquad(APlayerMarkerPlayerState* Player, ETeam Team, ESquadName SquadName);
	void RemovePlayerFromTeam(APlayerMarkerPlayerState* Player);
	void RemovePlayerFromSquad(APlayerMarkerPlayerState* Player);

	/** Returns the player count of the specified team */
	int32 GetTeamPlayerCount(ETeam Team);
};
