#include "PlayerMarkerWidget.h"
#include "Components/TextBlock.h"



void UPlayerMarkerWidget::SetUsername(FString NewUsername)
{
	if (TextUsername)
	{
		TextUsername->SetText(FText::FromString(NewUsername));
	}
}
