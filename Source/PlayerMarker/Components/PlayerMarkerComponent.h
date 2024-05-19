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

protected:
	virtual void BeginPlay() override;

private:
	/** Player marker widget component */
	UPROPERTY()
	UWidgetComponent* PlayerMarkerWidgetComponent;

	/** Player marker widget */
	UPROPERTY()
	UPlayerMarkerWidget* PlayerMarkerWidget;

	void UpdatePlayerMarker(AFirstPersonCharacter* LocallyControlledCharacter, 
		AFirstPersonCharacter* OtherCharacter);
	void HandleDifferentTeam(AFirstPersonCharacter* LocallyControlledCharacter,
		AFirstPersonCharacter* OtherCharacter);
	void HandleSameTeamDifferentSquad(AFirstPersonCharacter* LocallyControlledCharacter,
		AFirstPersonCharacter* OtherCharacter);
	void HandleSameTeamSameSquad(AFirstPersonCharacter* LocallyControlledCharacter,
		AFirstPersonCharacter* OtherCharacter);
	void RotatePlayerMarkerToPlayerCamera();
};
