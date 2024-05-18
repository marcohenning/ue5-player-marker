#include "PlayerMarkerGameMode.h"
#include "PlayerMarker/GameState/PlayerMarkerGameState.h"
#include "PlayerMarker/PlayerState/PlayerMarkerPlayerState.h"
#include "PlayerMarker/Enums/Enums.h"



void APlayerMarkerGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	/** Get game state and player state */
	APlayerMarkerGameState* PlayerMarkerGameState = GetGameState<APlayerMarkerGameState>();
	APlayerMarkerPlayerState* PlayerMarkerPlayerState = NewPlayer->GetPlayerState<APlayerMarkerPlayerState>();

	if (PlayerMarkerGameState && PlayerMarkerPlayerState)
	{
		/** Handle sorting players into teams and squads upon joining the game */
		InitializeSameTeamDifferentSquad(PlayerMarkerGameState, PlayerMarkerPlayerState);
	}
}

void APlayerMarkerGameMode::Logout(AController* Exiting)
{
	/** Get game state and player state */
	APlayerMarkerGameState* PlayerMarkerGameState = GetGameState<APlayerMarkerGameState>();
	APlayerMarkerPlayerState* PlayerMarkerPlayerState = Exiting->GetPlayerState<APlayerMarkerPlayerState>();

	if (PlayerMarkerGameState && PlayerMarkerPlayerState)
	{
		/** Remove player from team and squad */
		PlayerMarkerGameState->RemovePlayerFromTeam(PlayerMarkerPlayerState);
		PlayerMarkerGameState->RemovePlayerFromSquad(PlayerMarkerPlayerState);
	}
}

void APlayerMarkerGameMode::InitializeDifferentTeam(APlayerMarkerGameState* PlayerMarkerGameState, 
	APlayerMarkerPlayerState* PlayerMarkerPlayerState)
{
	/** Check if pointers are valid */
	if (PlayerMarkerGameState == nullptr || PlayerMarkerPlayerState == nullptr)
	{
		return;
	}

	/** Add first player to team a */
	if (PlayerMarkerGameState->GetTeamPlayerCount(ETeam::ET_TeamA) == 0)
	{
		PlayerMarkerGameState->AddPlayerToTeam(PlayerMarkerPlayerState, ETeam::ET_TeamA);
		PlayerMarkerGameState->AddPlayerToSquad(PlayerMarkerPlayerState, ETeam::ET_TeamA, ESquadName::ESN_Alpha);
	}
	/** Add all other players to team b */
	else
	{
		PlayerMarkerGameState->AddPlayerToTeam(PlayerMarkerPlayerState, ETeam::ET_TeamB);
		PlayerMarkerGameState->AddPlayerToSquad(PlayerMarkerPlayerState, ETeam::ET_TeamB, ESquadName::ESN_Alpha);
	}
}

void APlayerMarkerGameMode::InitializeSameTeamDifferentSquad(APlayerMarkerGameState* PlayerMarkerGameState, 
	APlayerMarkerPlayerState* PlayerMarkerPlayerState)
{
	/** Check if pointers are valid */
	if (PlayerMarkerGameState == nullptr || PlayerMarkerPlayerState == nullptr)
	{
		return;
	}

	/** Add first player to team a and squad alpha */
	if (PlayerMarkerGameState->GetTeamPlayerCount(ETeam::ET_TeamA) == 0)
	{
		PlayerMarkerGameState->AddPlayerToTeam(PlayerMarkerPlayerState, ETeam::ET_TeamA);
		PlayerMarkerGameState->AddPlayerToSquad(PlayerMarkerPlayerState, ETeam::ET_TeamA, ESquadName::ESN_Alpha);
	}
	/** Add all other players to team a and squad bravo */
	else
	{
		PlayerMarkerGameState->AddPlayerToTeam(PlayerMarkerPlayerState, ETeam::ET_TeamA);
		PlayerMarkerGameState->AddPlayerToSquad(PlayerMarkerPlayerState, ETeam::ET_TeamA, ESquadName::ESN_Bravo);
	}
}

void APlayerMarkerGameMode::InitializeSameTeamSameSquad(APlayerMarkerGameState* PlayerMarkerGameState, 
	APlayerMarkerPlayerState* PlayerMarkerPlayerState)
{
	/** Check if pointers are valid */
	if (PlayerMarkerGameState == nullptr || PlayerMarkerPlayerState == nullptr)
	{
		return;
	}

	/** Add all players to team a and squad alpha */
	PlayerMarkerGameState->AddPlayerToTeam(PlayerMarkerPlayerState, ETeam::ET_TeamA);
	PlayerMarkerGameState->AddPlayerToSquad(PlayerMarkerPlayerState, ETeam::ET_TeamA, ESquadName::ESN_Alpha);
}
