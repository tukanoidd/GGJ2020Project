// Property of OTNH 2020

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"

#include "Components/StaticMeshComponent.h"

#include "Item.generated.h"

UCLASS()
class GGJ2020PROJECT_API AItem : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AItem();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = Floating)
	bool bIsFloating;

	FVector InitialLocation;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = Mesh)
	UStaticMeshComponent* Mesh;

	// Floating wave settings
	UPROPERTY(EditAnywhere, Category = Floating)
	float Amplitude;
	UPROPERTY(EditAnywhere, Category = Floating)
	float Frequency;

	float RunningTime;

	/** Make item float */
	void Float(float DeltaTime);
};
