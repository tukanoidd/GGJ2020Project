// Property of OTNH 2020

#include "RepairableActor.h"

#include "GGJ2020Project/MainCharacter/MainCharacter.h"

#include "GameFramework/PlayerController.h"

// Sets default values
ARepairableActor::ARepairableActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
	Mesh->SetMobility(EComponentMobility::Static);

	RepairMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RepairMesh"));
	RepairMesh->SetupAttachment(GetRootComponent());
	RepairMesh->SetMobility(EComponentMobility::Static);

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	CollisionSphere->SetupAttachment(GetRootComponent());
	CollisionSphere->SetMobility(EComponentMobility::Static);

	ParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particles"));
	ParticleSystem->SetupAttachment(GetRootComponent());
	ParticleSystem->SetMobility(EComponentMobility::Static);

	SubtitleTriggerBox = nullptr;

	ToolToUse = nullptr;

	InteractionType = EInteractionType::EIT_Repair;
	InteractionTarget = nullptr;

	MainCharacter = nullptr;

	NameOfRepairable = TEXT("");
}

// Called when the game starts or when spawned
void ARepairableActor::BeginPlay()
{
	Super::BeginPlay();

	if (RepairMesh) RepairMesh->SetVisibility(false);

	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &ARepairableActor::OnOverlapBegin);
	CollisionSphere->OnComponentEndOverlap.AddDynamic(this, &ARepairableActor::OnOverlapEnd);

	MainCharacter = Cast<AMainCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (MainCharacter)
	{
		UInputComponent* PlayerInputComponent = MainCharacter->InputComponent;
		PlayerInputComponent->BindAction("Repair/Interact", IE_Pressed, this, &ARepairableActor::RepairInteract);
	}

	UE_LOG(LogTemp, Warning, TEXT("%s"), *ToolToUse->GetName())
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
	AMainCharacter* MainCharacterCheck = Cast<AMainCharacter>(OtherActor);
	if (MainCharacterCheck)
	{
		if (!MainCharacter) MainCharacter = MainCharacterCheck;

		MainCharacter->bInRepairArea = true;
	}
}

void ARepairableActor::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
									UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AMainCharacter* MainCharacterCheck = Cast<AMainCharacter>(OtherActor);
	if (MainCharacterCheck)
	{
		MainCharacterCheck->bInRepairArea = false;
	}
}

void ARepairableActor::RepairInteract()
{
	if (MainCharacter)
	{
		if (MainCharacter->bInRepairArea)
		{
			if (InteractionType == EInteractionType::EIT_Repair) Repair();
			if (InteractionType == EInteractionType::EIT_Interact) Interact();
		}
	}
}

void ARepairableActor::Repair()
{
	if (MainCharacter->PhysicsHandleComponent)
	{
		if (MainCharacter->PhysicsHandleComponent->GetGrabbedComponent())
		{
			AItem* ItemInHand = Cast<AItem>(MainCharacter->PhysicsHandleComponent->GetGrabbedComponent()->GetOwner());
			UE_LOG(LogTemp, Warning, TEXT("%s"), *ItemInHand->NameToShow)

			if (ItemInHand && ToolToUse)
			{
				UE_LOG(LogTemp, Warning, TEXT("%s, %s"), *ItemInHand->GetName(), *ToolToUse->GetName())
				if (ItemInHand->GetName() == ToolToUse->GetName())
				{
					UE_LOG(LogTemp, Warning, TEXT("Equal"))
					MainCharacter->GrabberComponent->Release();
					MainCharacter->GrabberComponent->GetGrabbedActor()->Destroy();

					if (RepairMesh) RepairMesh->SetVisibility(true);
					if (ParticleSystem) ParticleSystem->SetVisibility(false);

					if (CollisionSphere) CollisionSphere->DestroyComponent();
					if (SubtitleTriggerBox) SubtitleTriggerBox->Destroy();
				}
			}
		}
	}
}

void ARepairableActor::Interact()
{
	if (InteractionTarget && ToolToUse)
	{
		if (ToolToUse->NameToShow == "Crowbar")
		{
			UStaticMeshComponent* TargetMeshComponent = InteractionTarget->GetStaticMeshComponent();
			if (TargetMeshComponent)
			{
				TargetMeshComponent->SetMobility(EComponentMobility::Movable);
				TargetMeshComponent->SetSimulatePhysics(true);
				TargetMeshComponent->SetEnableGravity(false);
			}
		}
	}
}
