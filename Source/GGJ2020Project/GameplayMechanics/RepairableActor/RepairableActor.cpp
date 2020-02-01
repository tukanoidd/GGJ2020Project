// Property of OTNH 2020

#include "RepairableActor.h"

#include "GGJ2020Project/MainCharacter/MainCharacter.h"

// Sets default values
ARepairableActor::ARepairableActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
	Mesh->SetMobility(EComponentMobility::Static);

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	CollisionSphere->SetupAttachment(GetRootComponent());
	CollisionSphere->SetMobility(EComponentMobility::Static);
}

// Called when the game starts or when spawned
void ARepairableActor::BeginPlay()
{
	Super::BeginPlay();

	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &ARepairableActor::OnOverlapBegin);
	CollisionSphere->OnComponentEndOverlap.AddDynamic(this, &ARepairableActor::OnOverlapEnd);
}

// Called every frame
void ARepairableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ARepairableActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult)
{
	AMainCharacter* MainCharacter = Cast<AMainCharacter>(OtherActor);
	if (MainCharacter)
	{
		UE_LOG(LogTemp, Warning, TEXT("In Repair Area"))
		MainCharacter->bInRepairArea = true;
	}
}

void ARepairableActor::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AMainCharacter* MainCharacter = Cast<AMainCharacter>(OtherActor);
	if (MainCharacter)
	{
		MainCharacter->bInRepairArea = false;
	}
}