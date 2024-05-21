#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PlayerMarker/Enums/Enums.h"
#include "PlayerMarkerGameMode.generated.h"



class APlayerMarkerGameState;
class APlayerMarkerPlayerState;



UCLASS()
class PLAYERMARKER_API APlayerMarkerGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;

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
