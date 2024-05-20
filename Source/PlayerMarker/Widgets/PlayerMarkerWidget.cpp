#include "PlayerMarkerWidget.h"
#include "Components/TextBlock.h"
#include "Components/Progressbar.h"



void UPlayerMarkerWidget::SetPlayerName(FString NewUsername)
{
	if (TextPlayerName)
	{
		TextPlayerName->SetText(FText::FromString(NewUsername));
	}
}

void UPlayerMarkerWidget::SetPlayerNameColor(FLinearColor Color)
{
	if (TextPlayerName)
	{
		TextPlayerName->SetColorAndOpacity(FSlateColor(Color));
	}
}

void UPlayerMarkerWidget::SetHealthBarColor(FLinearColor Color, FLinearColor ColorTransparent)
{
	if (HealthBar)
	{
		HealthBar->SetFillColorAndOpacity(Color);
		/** TODO: Set rest of the colors here aswell */
	}
}
