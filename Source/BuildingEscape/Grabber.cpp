// IndicoGames 2017

#include "Grabber.h"

#define OUT


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	InitAttachedPhysicsHandle();
	InitAttachedInput();
	
}

void UGrabber::InitAttachedPhysicsHandle()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle) {

	}
	else {
		UE_LOG(LogTemp, Error, TEXT("PhysicsHandleComponent missing in %s"), *(GetOwner()->GetName()))
	}
}
void UGrabber::InitAttachedInput()
{
	Input = GetOwner()->FindComponentByClass<UInputComponent>();
	if (Input) {
		Input->BindAction("Grab", IE_Pressed, this, &UGrabber::GrabInputPressed);
		Input->BindAction("Grab", IE_Released, this, &UGrabber::GrabInputReleased);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("InputComponent missing in %s"), *(GetOwner()->GetName()))
	}

}

void UGrabber::GrabInputPressed() {
	UE_LOG(LogTemp, Warning, TEXT("Grab pressed in %s"), *(GetOwner()->GetName()))
}

void UGrabber::GrabInputReleased() {
	UE_LOG(LogTemp, Warning, TEXT("Grab released in %s"), *(GetOwner()->GetName()))
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);
	/*UE_LOG(LogTemp, Warning, TEXT("Location: %s; Rotation: %s"),
		*PlayerViewPointLocation.ToString(),
		*PlayerViewPointRotation.ToString()
	);*/

	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * DebugLineVectorReach;

	DrawDebugLine(
		GetWorld(),
		PlayerViewPointLocation,
		LineTraceEnd,
		FColor(255,0,0),
		false,
		0.f,
		0.f,
		5.f
	);

	/// Setup query Parameters
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	/// Line Trace (aka ray-cast) out to reach distance
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);

	/// Catch Hits 
	AActor* ActorHit = Hit.GetActor();
	if (ActorHit) {
		UE_LOG(LogTemp, Warning, TEXT("Line trace hit: %s"), *(ActorHit->GetName()))
	}
}
