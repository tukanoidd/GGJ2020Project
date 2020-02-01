// Property of OTNH 2020

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"

#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"

#include "GGJ2020Project/MainCharacter/MainCharacter.h"
#include "GGJ2020Project/GameplayMechanics/Item/Item.h"

#include "Engine/StaticMeshActor.h"

#include "RepairableActor.generated.h"

UENUM(BlueprintType)
enum class EInteractionType : uint8
{
	EIT_Interact UMETA(DisplayName = "Interact"),
	EIT_Repair UMETA(DisplayName = "Repair"),

	EIT_MAX UMETA(DisplayName = "DefaultMax")
};

UCLASS()
class GGJ2020PROJECT_API ARepairableActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARepairableActor();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = Mesh)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly, Category = Mesh)
	UStaticMeshComponent* RepairMesh;

	UPROPERTY(EditDefaultsOnly, Category = Collision)
	USphereComponent* CollisionSphere;

	UPROPERTY(EditAnywhere, Category = Info)
	AItem* ToolToUse;

	UPROPERTY(EditAnywhere, Category = Info)
	EInteractionType InteractionType;

	UPROPERTY(EditAnywhere, Category = Info)
	AStaticMeshActor* InteractionTarget;

	UPROPERTY(EditAnywhere, Category = Info)
	FString NameOfRepairable;

	AMainCharacter* MainCharacter;
	
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
						int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
					  int32 OtherBodyIndex);

	void RepairInteract();

	void Repair();
	void Interact();
};
