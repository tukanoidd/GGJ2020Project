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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Items)
	AActor* LastSeenItem;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Items)
	bool bLookingAtItem;

	void Release();

	FORCEINLINE AActor* GetGrabbedActor() { return GrabbedActor; }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = Reach)
	float Reach;

	UPhysicsHandleComponent* PhysicsHandle;
	UInputComponent* InputComponent;

	UPrimitiveComponent* LastSeenItemComponent;

	AActor* GrabbedActor;
	UPrimitiveComponent* GrabbedComponent;
	FVector LineStartLocation;
	FVector GrabLocation;

	bool bGrabbed;

	void SetupInputComponent();

	void CheckGrab();
	void Grab();

	void UpdateGrabLocation();

	void CheckLookingAtItem();
};
