#include "PlayerMarkerWidget.h"
#include "Components/TextBlock.h"
#include "Components/Progressbar.h"
#include "Components/Image.h"
#include "Components/SizeBox.h"



void UPlayerMarkerWidget::SetPlayerName(FString NewUsername)
{
	if (TextPlayerName)
	{
		TextPlayerName->SetText(FText::FromString(NewUsername));
	}
}

void UPlayerMarkerWidget::SetDistance(int32 Distance)
{
	if (TextDistance)
	{
		FString DistanceText = FString::Printf(TEXT("%d m"), Distance);
		TextDistance->SetText(FText::FromString(DistanceText));
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

void UPlayerMarkerWidget::ShowDistance()
{
	if (TextDistance && TextDistance->GetVisibility() != ESlateVisibility::Visible)
	{
		TextDistance->SetVisibility(ESlateVisibility::Visible);
	}
}

void UPlayerMarkerWidget::ShowHealthBar()
{
	if (SizeBoxHealthBar && SizeBoxHealthBar->GetVisibility() != ESlateVisibility::Visible)
	{
		SizeBoxHealthBar->SetVisibility(ESlateVisibility::Visible);
	}
}

void UPlayerMarkerWidget::HideDistance()
{
	if (TextDistance && TextDistance->GetVisibility() != ESlateVisibility::Collapsed)
	{
		TextDistance->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UPlayerMarkerWidget::HideHealthBar()
{
	if (SizeBoxHealthBar && SizeBoxHealthBar->GetVisibility() != ESlateVisibility::Collapsed)
	{
		SizeBoxHealthBar->SetVisibility(ESlateVisibility::Collapsed);
	}
}
