#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerMarkerWidget.generated.h"



class UTextBlock;
class UProgressBar;



UCLASS()
class PLAYERMARKER_API UPlayerMarkerWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	const FLinearColor ColorEnemy = FLinearColor(1.0f, 0.023529f, 0.0f, 1.0f);
	const FLinearColor ColorEnemyTransparent = FLinearColor(1.0f, 0.023529f, 0.0f, 0.2f);
	const FLinearColor ColorTeam = FLinearColor();
	const FLinearColor ColorTeamTransparent = FLinearColor();
	const FLinearColor ColorSquad = FLinearColor();
	const FLinearColor ColorSquadTransparent = FLinearColor();

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TextPlayerName;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TextDistance;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* HealthBar;

	void SetPlayerName(FString NewUsername);
	void SetDistance(FString NewDistance);
	void SetPlayerNameColor(FLinearColor Color);
	void SetHealthBarColor(FLinearColor Color, FLinearColor ColorTransparent);
};
