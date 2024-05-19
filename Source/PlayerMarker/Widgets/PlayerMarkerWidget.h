#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerMarkerWidget.generated.h"



class UTextBlock;



UCLASS()
class PLAYERMARKER_API UPlayerMarkerWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TextUsername;

	void SetUsername(FString NewUsername);
};
