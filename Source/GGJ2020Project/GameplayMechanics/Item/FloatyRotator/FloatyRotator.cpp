// Property of OTNH 2020

#include "FloatyRotator.h"

#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UFloatyRotator::UFloatyRotator()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	ActorMesh = nullptr;

	MaxForcePower = 100.f;

	RotationForce = FRotator::ZeroRotator;
}


// Called when the game starts
void UFloatyRotator::BeginPlay()
{
	Super::BeginPlay();

	ActorMesh = GetOwner()->FindComponentByClass<UMeshComponent>();

	if (ActorMesh)
	{
		ActorMesh->SetMobility(EComponentMobility::Movable);
		ActorMesh->SetEnableGravity(false);
		
		RotationForce = FRotator(
			FMath::FRandRange(30, MaxForcePower),
			FMath::FRandRange(30, MaxForcePower),
			FMath::FRandRange(30, MaxForcePower)
		);
	}
}


// Called every frame
void UFloatyRotator::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FRotator ActorRotation = GetOwner()->GetActorRotation();
	ActorRotation.Yaw += RotationForce.Yaw * DeltaTime;
	ActorRotation.Pitch += RotationForce.Pitch * DeltaTime;
	ActorRotation.Roll += RotationForce.Roll * DeltaTime;

	GetOwner()->SetActorRotation(ActorRotation);
}
