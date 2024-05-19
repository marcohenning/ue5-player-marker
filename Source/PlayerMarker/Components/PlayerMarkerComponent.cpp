#include "PlayerMarkerComponent.h"
#include "PlayerMarker/Widgets/PlayerMarkerWidget.h"



UPlayerMarkerComponent::UPlayerMarkerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPlayerMarkerComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UPlayerMarkerComponent::TickComponent(float DeltaTime, ELevelTick TickType, 
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PlayerMarkerWidget)
	{
		PlayerMarkerWidget->SetUsername("Test");
	}
}
