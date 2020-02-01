// Property of OTNH 2020

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Character.h"

#include "Components/StaticMeshComponent.h"

#include "Camera/CameraComponent.h"

#include "PhysicsEngine/PhysicsHandleComponent.h"

#include "GGJ2020Project/MainCharacter/Grabber/Grabber.h"

#include "MainCharacter.generated.h"

UCLASS()
class GGJ2020PROJECT_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleDefaultsOnly, Category = Physics)
	UPhysicsHandleComponent* PhysicsHandleComponent;

	UPROPERTY(EditDefaultsOnly, Category = Camera)
	UCameraComponent* Camera;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Grabbing)
	UGrabber* GrabberComponent;

	UPROPERTY(BlueprintReadOnly, Category = Repair)
	bool bInRepairArea;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	/** Character body and world settings */
	UPROPERTY(EditDefaultsOnly, Category = Character)
	float Mass;
	UPROPERTY(EditDefaultsOnly, Category = Character)
	float GravityScale;

	/** Movement Settings */
	UPROPERTY(EditDefaultsOnly, Category = Movement)
	float RunningSpeed;
	UPROPERTY(EditDefaultsOnly, Category = Movement)
	float JumpVelocity;
	UPROPERTY(EditDefaultsOnly, Category = Movement)
	float AirControl;

	/** Movement functions */
	void MoveForward(float Value);
	void MoveRight(float Value);
};
