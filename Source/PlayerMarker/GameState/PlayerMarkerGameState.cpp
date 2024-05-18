#include "PlayerMarkerGameState.h"
#include "Net/UnrealNetwork.h"
#include "PlayerMarker/PlayerState/PlayerMarkerPlayerState.h"



void APlayerMarkerGameState::InitializeSquads(ETeam Team)
{
	FSquad Squad;
	Squad.Team = Team;

	Squad.Name = ESquadName::ESN_Alpha;
	Squads.Emplace(Squad);

	Squad.Name = ESquadName::ESN_Bravo;
	Squads.Emplace(Squad);

	Squad.Name = ESquadName::ESN_Charlie;
	Squads.Emplace(Squad);

	Squad.Name = ESquadName::ESN_Delta;
	Squads.Emplace(Squad);

	Squad.Name = ESquadName::ESN_Echo;
	Squads.Emplace(Squad);

	Squad.Name = ESquadName::ESN_Foxtrot;
	Squads.Emplace(Squad);

	Squad.Name = ESquadName::ESN_Golf;
	Squads.Emplace(Squad);

	Squad.Name = ESquadName::ESN_Hotel;
	Squads.Emplace(Squad);
}

APlayerMarkerGameState::APlayerMarkerGameState()
{
	InitializeSquads(ETeam::ET_TeamA);
	InitializeSquads(ETeam::ET_TeamB);
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

void APlayerMarkerGameState::AddPlayerToTeam(APlayerMarkerPlayerState* Player, ETeam Team)
{
	FPlayerInformation PlayerInformation;
	PlayerInformation.PlayerState = Player;
	PlayerInformation.Team = Team;
	Players.Emplace(PlayerInformation);

	Player->Team = Team;
}

void APlayerMarkerGameState::AddPlayerToSquad(APlayerMarkerPlayerState* Player, ETeam Team,
	ESquadName SquadName)
{
	for (FSquad& Squad : Squads)
	{
		if (Squad.Team == Team && Squad.Name == SquadName)
		{
			Squad.Members.AddUnique(Player);
		}
	}
	Player->Squad = SquadName;
}

void APlayerMarkerGameState::RemovePlayerFromTeam(APlayerMarkerPlayerState* Player)
{
	for (int32 i = 0; i < Players.Num(); i++)
	{
		if (Players[i].PlayerState == Player)
		{
			Players.RemoveAt(i);
			break;
		}
	}
}

void APlayerMarkerGameState::RemovePlayerFromSquad(APlayerMarkerPlayerState* Player)
{
	for (int32 i = 0; i < Squads.Num(); i++)
	{
		if (Squads[i].Members.Contains(Player))
		{
			Squads[i].Members.Remove(Player);
			break;
		}
	}
}

int32 APlayerMarkerGameState::GetTeamPlayerCount(ETeam Team)
{
	int32 Count = 0;

	for (FPlayerInformation PlayerInformation : Players)
	{
		if (PlayerInformation.Team == Team)
		{
			Count++;
		}
	}
	return Count;
}
