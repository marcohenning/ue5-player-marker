#include "PlayerMarkerComponent.h"



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
}
