// Property of OTNH 2020

#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"
#include "Components/MeshComponent.h"

#include "FloatyRotator.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GGJ2020PROJECT_API UFloatyRotator : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFloatyRotator();
	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UMeshComponent* ActorMesh;
	
	UPROPERTY(EditAnywhere, Category = Rotation)
	float MaxForcePower;

	FRotator RotationForce;
};
