#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerMarkerWidget.generated.h"



class UTextBlock;
class UProgressBar;
class UImage;
class USizeBox;



UCLASS()
class PLAYERMARKER_API UPlayerMarkerWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	/**
	* Player marker colors
	*/
	const FLinearColor ColorEnemy = FLinearColor(1.0f, 0.023529f, 0.0f, 1.0f);
	const FLinearColor ColorEnemyTransparent = FLinearColor(1.0f, 0.023529f, 0.0f, 0.2f);
	const FLinearColor ColorTeam = FLinearColor(0.0f, 0.701961f, 1.0f, 1.0f);
	const FLinearColor ColorTeamTransparent = FLinearColor(0.0f, 0.701961f, 1.0f, 0.2f);
	const FLinearColor ColorSquad = FLinearColor(0.215686f, 1.0f, 0.0f, 1.0f);
	const FLinearColor ColorSquadTransparent = FLinearColor(0.215686f, 1.0f, 0.0f, 0.2f);

	/**
	* Player marker icons
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* IconEnemy;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* IconTeam;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* IconSquad;

	/**
	* Widget elements
	*/
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TextPlayerName;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TextDistance;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* HealthBar;

	UPROPERTY(meta = (BindWidget))
	USizeBox* SizeBoxHealthBar;

	UPROPERTY(meta = (BindWidget))
	UImage* ImageMarkerIcon;

	/**
	* Setters for different widget properties
	*/
	void SetPlayerName(FString NewUsername);
	void SetDistance(int32 Distance);
	void SetPlayerNameColor(FLinearColor Color);
	void SetDistanceColor(FLinearColor Color);
	void SetHealthBarColor(FLinearColor Color, FLinearColor ColorTransparent);
	void SetIcon(UTexture2D* Icon);

	/**
	* Functions to show and hide elements
	*/
	void ShowPlayerName();
	void ShowDistance();
	void ShowHealthBar();
	void ShowImageMarkerIcon();
	void HidePlayerName();
	void HideDistance();
	void HideHealthBar();
	void HideImageMarkerIcon();
};
