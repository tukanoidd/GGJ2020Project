// Property of OTNH 2020

#include "Grabber.h"

#include "Engine/World.h"

#include "GameFramework/PlayerController.h"

#include "GGJ2020Project/GameplayMechanics/Item/Item.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	Reach = 300.f;

	PhysicsHandle = nullptr;
	InputComponent = nullptr;

	LastSeenItem = nullptr;
	LastSeenItemComponent = nullptr;

	bLookingAtItem = false;

	GrabbedActor = nullptr;
	GrabbedComponent = nullptr;
	LineStartLocation = FVector::ZeroVector;
	GrabLocation = FVector::ZeroVector;
	bGrabbed = false;
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!PhysicsHandle) UE_LOG(LogTemp, Warning, TEXT("No PhysicsHandle"))
	
	SetupInputComponent();
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	CheckLookingAtItem();

	if (PhysicsHandle)
	{
		if (bGrabbed)
		{
			UpdateGrabLocation();
			PhysicsHandle->SetTargetLocation(GrabLocation);
		}
	}
}

void UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	if (InputComponent)
	{
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::CheckGrab);
	} else UE_LOG(LogTemp, Warning, TEXT("No InputComponent"))
}

void UGrabber::CheckGrab()
{
	if (PhysicsHandle)
	{
		if (!bGrabbed)
		{
			if (bLookingAtItem && LastSeenItem && LastSeenItemComponent) Grab();
		} 
		else if (PhysicsHandle->GetGrabbedComponent() && GrabbedComponent && GrabbedActor) Release();
	}
}

void UGrabber::Grab()
{
	AItem* ItemToGrab = Cast<AItem>(LastSeenItem);
	if (ItemToGrab) ItemToGrab->bIsFloating = false;

	UMeshComponent* MeshToGrab = Cast<UMeshComponent>(LastSeenItemComponent);
	if (MeshToGrab) MeshToGrab->SetEnableGravity(true);

	PhysicsHandle->GrabComponentAtLocation(
		LastSeenItemComponent,
		NAME_None,
		GrabLocation
	);
	PhysicsHandle->bRotationConstrained = true;

	GrabbedActor = LastSeenItem;
	GrabbedComponent = LastSeenItemComponent;
	
	bGrabbed = true;
}

void UGrabber::Release()
{
	FVector LastInHandLocation = GrabbedComponent->GetComponentLocation();
	
	AItem* ItemToRelease = Cast<AItem>(GrabbedActor);
	if (ItemToRelease)
	{
		ItemToRelease->bIsFloating = true;
		ItemToRelease->InitialLocation = LastInHandLocation;
	}

	UMeshComponent* MeshToRelease = Cast<UMeshComponent>(GrabbedComponent);
	if (MeshToRelease) MeshToRelease->SetEnableGravity(false);
	
	PhysicsHandle->ReleaseComponent();

	GrabbedActor->SetActorLocation(LastInHandLocation);

	bGrabbed = false;
}

void UGrabber::CheckLookingAtItem()
{
	FHitResult Hit;
	FCollisionQueryParams Params(
		FName(TEXT("")),
		false,
		GetOwner()
	);

	UpdateGrabLocation();
	
	GetWorld()->LineTraceSingleByObjectType(
		Hit,
		LineStartLocation,
		GrabLocation,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		Params
	);

	if (Hit.GetActor())
	{
		LastSeenItem = Hit.GetActor();
		LastSeenItemComponent = Hit.GetComponent();
		bLookingAtItem = true;
	}
	else
	{
		bLookingAtItem = false;
	}
}

void UGrabber::UpdateGrabLocation()
{
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		LineStartLocation,
		PlayerViewPointRotation
	);

	GrabLocation = LineStartLocation + PlayerViewPointRotation.Vector() * Reach;
}
