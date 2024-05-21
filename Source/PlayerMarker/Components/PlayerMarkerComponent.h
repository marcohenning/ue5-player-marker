#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerMarkerComponent.generated.h"



class AFirstPersonCharacter;
class UWidgetComponent;
class UPlayerMarkerWidget;



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PLAYERMARKER_API UPlayerMarkerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPlayerMarkerComponent();
	friend class AFirstPersonCharacter;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& 
		OutLifetimeProps) const override;

private:
	/** Are player name, colors and icon initalized? */
	bool bPlayerMarkerInitialized = false;

	/** Is player spotted? */
	UPROPERTY(Replicated)
	bool bSpotted = false;

	/** Timer for resetting the bSpotted flag */
	FTimerHandle SpotTimer;

	/** Duration players are spotted for */
	float SpotDuration = 10.0f;

	/** Constants for player marker handling */
	const int32 EnemyMaxDistance = 10;
	const int32 TeamMaxDistance = 20;
	const int32 SquadMaxDistance = 15;

	/** Player marker widget component */
	UPROPERTY()
	UWidgetComponent* PlayerMarkerWidgetComponent;

	/** Player marker widget */
	UPROPERTY()
	UPlayerMarkerWidget* PlayerMarkerWidget;

	/** Called once at the start to initalize player name, colors and icon */
	bool InitializePlayerMarkerComponent(AFirstPersonCharacter* LocallyControlledCharacter,
		AFirstPersonCharacter* OtherCharacter);

	/** Called every tick from character to update the player marker widget */
	void UpdatePlayerMarker(AFirstPersonCharacter* LocallyControlledCharacter, 
		AFirstPersonCharacter* OtherCharacter);

	/**
	* Functions to handle enemy, team mate and squad mate player marker
	*/
	void HandleEnemy(AFirstPersonCharacter* LocallyControlledCharacter,
		AFirstPersonCharacter* OtherCharacter);
	void HandleTeam(AFirstPersonCharacter* LocallyControlledCharacter,
		AFirstPersonCharacter* OtherCharacter);
	void HandleSquad(AFirstPersonCharacter* LocallyControlledCharacter,
		AFirstPersonCharacter* OtherCharacter);

	/** Calculates distance in meters between two vectors */
	float CalculateDistance(FVector Start, FVector End);

	/** Check if the locally controlled character is looking at the other character */
	bool LocalCharacterLookingAtOtherCharacter(AFirstPersonCharacter* OtherCharacter);

	/**
	* Called by the server when this component's character is spotted.
	* Handles setting bSpotted to true and (re)starting the timer to reset it.
	*/
	void Spot();

	/** Callback function for the timer resetting the bSpotted flag */
	void SpotTimerFinished();
};
