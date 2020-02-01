// Property of OTNH 2020

#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"
#include "Components/InputComponent.h"

#include "PhysicsEngine/PhysicsHandleComponent.h"

#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GGJ2020PROJECT_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UGrabber();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
	override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = Reach)
	float Reach;

	UPhysicsHandleComponent* PhysicsHandle;
	UInputComponent* InputComponent;

	AActor* LastSeenItem;
	UPrimitiveComponent* LastSeenItemComponent;
	bool bLookingAtItem;

	AActor* GrabbedActor;
	UPrimitiveComponent* GrabbedComponent;
	FVector LineStartLocation;
	FVector GrabLocation;

	bool bGrabbed;

	void SetupInputComponent();

	void CheckGrab();
	void Grab();
	void Release();

	void UpdateGrabLocation();

	void CheckLookingAtItem();
};
