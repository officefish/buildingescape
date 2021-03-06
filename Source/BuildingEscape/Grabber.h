// IndicoGames 2017

#pragma once

#include "Engine.h"
#include "Components/ActorComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	float DebugLineVectorReach = 100.f;
	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UInputComponent * Input = nullptr;

	void GrabInputPressed();
	void GrabInputReleased();

	void InitAttachedPhysicsHandle();
	void InitAttachedInput();

	void LogPhysicsHandleMissingError();

	FVector GetReachLineStart();
	FVector GetReachLineEnd();

	const FHitResult GetFirstPhysicsBodyInReach();
};
