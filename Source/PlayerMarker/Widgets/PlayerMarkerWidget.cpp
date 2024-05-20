#include "PlayerMarkerWidget.h"
#include "Components/TextBlock.h"
#include "Components/Progressbar.h"
#include "Components/Image.h"



void UPlayerMarkerWidget::SetPlayerName(FString NewUsername)
{
	if (TextPlayerName)
	{
		TextPlayerName->SetText(FText::FromString(NewUsername));
	}
}

void UPlayerMarkerWidget::SetDistance(FString NewDistance)
{
	if (TextDistance)
	{
		TextDistance->SetText(FText::FromString(NewDistance));
	}
}

void UPlayerMarkerWidget::SetPlayerNameColor(FLinearColor Color)
{
	if (TextPlayerName)
	{
		TextPlayerName->SetColorAndOpacity(FSlateColor(Color));
	}
}

void UPlayerMarkerWidget::SetDistanceColor(FLinearColor Color)
{
	if (TextDistance)
	{
		TextDistance->SetColorAndOpacity(FSlateColor(Color));
	}
}

void UPlayerMarkerWidget::SetHealthBarColor(FLinearColor Color, FLinearColor ColorTransparent)
{
	if (HealthBar)
	{
		HealthBar->SetFillColorAndOpacity(Color);

		/** Set background and outline color */
		FProgressBarStyle Style = HealthBar->GetWidgetStyle();
		Style.BackgroundImage.OutlineSettings.Color = FSlateColor(Color);
		Style.BackgroundImage.TintColor = FSlateColor(ColorTransparent);
		HealthBar->SetWidgetStyle(Style);
	}
}

void UPlayerMarkerWidget::SetIcon(UTexture2D* Icon)
{
	if (ImageMarkerIcon && Icon)
	{
		ImageMarkerIcon->SetBrushFromTexture(Icon);
	}
}
