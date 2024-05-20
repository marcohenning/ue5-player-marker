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

	/**
	* Variables used for calculating widget render scale based on distance
	*/
	const float MinDistance = 0.0f;
	const float MaxDistance = 40.0f;
	const float MinRenderScale = 0.333f;
	const float MaxRenderScale = 1.0f;

	const int32 SquadMaxHealthBarDistance = 15;

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
	void HandleDifferentTeam(AFirstPersonCharacter* LocallyControlledCharacter,
		AFirstPersonCharacter* OtherCharacter);
	void HandleSameTeamDifferentSquad(AFirstPersonCharacter* LocallyControlledCharacter,
		AFirstPersonCharacter* OtherCharacter);
	void HandleSameTeamSameSquad(AFirstPersonCharacter* LocallyControlledCharacter,
		AFirstPersonCharacter* OtherCharacter);

	/** Calculates distance in meters between two vectors */
	float CalculateDistance(FVector Start, FVector End);

	/** Calculates widget size based on distance to locally controlled player */
	void CalculateWidgetSize(AFirstPersonCharacter* LocallyControlledCharacter, 
		AFirstPersonCharacter* OtherCharacter);

	/**
	* Called by the server when this component's character is spotted.
	* Handles setting bSpotted to true and (re)starting the timer to reset it.
	*/
	void Spot();
};
