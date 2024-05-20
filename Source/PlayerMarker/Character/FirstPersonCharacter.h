#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerMarker/Enums/Enums.h"
#include "FirstPersonCharacter.generated.h"



class APlayerMarkerPlayerState;
class UCameraComponent;
class UWidgetComponent;
class UPlayerMarkerComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;



UCLASS()
class PLAYERMARKER_API AFirstPersonCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AFirstPersonCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	ETeam GetTeam();
	ESquadName GetSquad();

protected:
	virtual void BeginPlay() override;

private:
	/** Locally controlled character */
	UPROPERTY()
	AFirstPersonCharacter* LocallyControlledCharacter;

	/** Player state */
	UPROPERTY()
	APlayerMarkerPlayerState* PlayerMarkerPlayerState;

	/** First person camera component */
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* FirstPersonCamera;

	/** Player marker component */
	UPROPERTY(VisibleAnywhere)
	UPlayerMarkerComponent* PlayerMarkerComponent;

	/** Player marker widget component */
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* PlayerMarkerWidgetComponent;

	/** Character mapping context */
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* MappingContextCharacter;

	/** Input action for basic movement */
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Input action for looking around */
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	/** Input action for jumping */
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Input action for spotting */
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	UInputAction* SpotAction;

	/** Crosshair widget class added to the viewport in beginplay */
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> CrosshairWidgetClass;

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	/** Called when the spot button is pressed */
	void SpotButtonPressed();

	/** Server rpc to validate spotting */
	UFUNCTION(Server, Unreliable)
	void ServerRequestSpot(FVector ViewportCenterWorldPosition, FVector ViewportCenterWorldDirection);
};
