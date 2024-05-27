#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PlayerMarker/Enums/Enums.h"
#include "PlayerMarkerGameMode.generated.h"


class APlayerMarkerGameState;
class APlayerMarkerPlayerState;


/**
* Custom game mode used for sorting joining players into teams and squads.
*/
UCLASS()
class PLAYERMARKER_API APlayerMarkerGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	/** Overriding functions for login and logout to react to players joining and leaving */
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;

	/** Method for sorting the joining players into teams and squads */
	UPROPERTY(EditAnywhere)
	ETeamSort TeamSort = ETeamSort::ETS_Enemy;

private:
	/**
	* Different hardcoded ways of sorting players into teams
	* and squads for testing purposes.
	*/
	void InitializeTypeEnemy(APlayerMarkerGameState* PlayerMarkerGameState, 
		APlayerMarkerPlayerState* PlayerMarkerPlayerState);
	void InitializeTypeTeam(APlayerMarkerGameState* PlayerMarkerGameState,
		APlayerMarkerPlayerState* PlayerMarkerPlayerState);
	void InitializeTypeSquad(APlayerMarkerGameState* PlayerMarkerGameState,
		APlayerMarkerPlayerState* PlayerMarkerPlayerState);
	void InitializeTypeAll(APlayerMarkerGameState* PlayerMarkerGameState,
		APlayerMarkerPlayerState* PlayerMarkerPlayerState);
};
