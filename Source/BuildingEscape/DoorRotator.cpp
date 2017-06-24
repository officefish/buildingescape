// IndicoGames 2017

#include "DoorRotator.h"
#include "Gameframework/Actor.h"

#define OUT

// Sets default values for this component's properties
UDoorRotator::UDoorRotator()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDoorRotator::BeginPlay()
{
	Super::BeginPlay();
	if (PressurePlate == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("PressurePlate not init in %s"), *(GetOwner()->GetName()))
	}
}


// Called every frame
void UDoorRotator::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if (GetTotalMassOfActorsOnPlane() > TriggerMass) {
		OnOpenEvent.Broadcast();
	} else {
		OnCloseEvent.Broadcast();
	}
}

float UDoorRotator::GetTotalMassOfActorsOnPlane() {
	float TotalMass = 0.f;
	
	if (PressurePlate == nullptr) {
		return TotalMass;
	}
		
	TArray<AActor*> OverlappingActors;
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);

	for (const auto& Actor : OverlappingActors)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}
	return TotalMass;
}

