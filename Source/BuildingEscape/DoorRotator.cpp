// IndicoGames 2017

#include "DoorRotator.h"
#include "Gameframework/Actor.h"

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

	// ...
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
	Owner = GetOwner();
	
}

void UDoorRotator::OpenDoor() {
	Owner->SetActorRotation(FRotator(0.f, OpenAngle, 0.f));
}

void UDoorRotator::CloseDoor() {
	Owner->SetActorRotation(FRotator(0.f, 0.f, 0.f));
}


// Called every frame
void UDoorRotator::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if (PressurePlate->IsOverlappingActor(ActorThatOpens)) {
		OpenDoor();
	}
}

