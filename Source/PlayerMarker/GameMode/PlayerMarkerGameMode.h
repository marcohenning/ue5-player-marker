#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
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

private:
	/**
	* Different hardcoded ways of sorting players into teams
	* and squads for testing purposes.
	*/
	void InitializeDifferentTeam(APlayerMarkerGameState* PlayerMarkerGameState, 
		APlayerMarkerPlayerState* PlayerMarkerPlayerState);
	void InitializeSameTeamDifferentSquad(APlayerMarkerGameState* PlayerMarkerGameState,
		APlayerMarkerPlayerState* PlayerMarkerPlayerState);
	void InitializeSameTeamSameSquad(APlayerMarkerGameState* PlayerMarkerGameState,
		APlayerMarkerPlayerState* PlayerMarkerPlayerState);
};
