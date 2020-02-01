// Property of OTNH 2020

#include "Item.h"

// Sets default values
AItem::AItem()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Setup item mesh
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(GetRootComponent());

	// Setup floating wave settings
	Amplitude = 10.f;
	Frequency = 10.f;

	bIsFloating = false;

	InitialLocation = FVector::ZeroVector;

	RunningTime = 0.f;

	NameToShow = "Item";
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();

	Mesh->SetSimulatePhysics(true);
	Mesh->SetEnableGravity(false);
	Mesh->BodyInstance.bLockXRotation = true;
	Mesh->BodyInstance.bLockYRotation = true;
	Mesh->BodyInstance.bLockZRotation = true;

	InitialLocation = GetActorLocation();
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsFloating) Float(DeltaTime);
}

void AItem::Float(float DeltaTime)
{
	float DeltaHeight = FMath::Sin((RunningTime + DeltaTime) * Frequency) * Amplitude;
	SetActorLocation(InitialLocation + FVector::UpVector * DeltaHeight);

	RunningTime += DeltaTime;
}
