#pragma once



UENUM()
enum class ETeam : uint8
{
	ET_TeamA,
	ET_TeamB,
	ET_TeamNone
};

UENUM()
enum class ESquadName : uint8
{
	ESN_Alpha,
	ESN_Bravo,
	ESN_Charlie,
	ESN_Delta,
	ESN_Echo,
	ESN_Foxtrot,
	ESN_Golf,
	ESN_Hotel,
	ESN_None
};

UENUM(BlueprintType)
enum class ETeamSort : uint8
{
	ETS_Enemy UMETA(DisplayName = "Enemy"),
	ETS_Team UMETA(DisplayName = "Team"),
	ETS_Squad UMETA(DisplayName = "Squad")
};
