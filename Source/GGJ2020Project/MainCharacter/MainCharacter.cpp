// Property of OTNH 2020

#include "MainCharacter.h"

#include "GameFramework/Controller.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Components/InputComponent.h"
#include "Components/SkeletalMeshComponent.h"

#include "Engine/World.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Setup camera
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(GetMesh());
	Camera->bUsePawnControlRotation = true;

	GrabberComponent = CreateDefaultSubobject<UGrabber>(TEXT("GrabberComponent"));

	PhysicsHandleComponent = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("PhysicsHandleComponent"));
	
	// Setup rotation
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = true;

	// Setup character body and world settings
	Mass = 100.f;
	GravityScale = 0.2f;

	// Setup movement settings
	RunningSpeed = 600.f;
	JumpVelocity = 300.f;
	AirControl = 1.f;

	// Setup CharacterMovementComponent
	GetCharacterMovement()->Mass = Mass;
	GetCharacterMovement()->GravityScale = GravityScale;
	GetCharacterMovement()->MaxWalkSpeed = RunningSpeed;
	GetCharacterMovement()->JumpZVelocity = JumpVelocity;
	GetCharacterMovement()->AirControl = AirControl;

	bInRepairArea = false;
	SubtitleText = TEXT("");
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMainCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
}

void AMainCharacter::MoveForward(float Value)
{
	if (Controller && Value != 0.f)
	{
		//Find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AMainCharacter::MoveRight(float Value)
{
	if (Controller && Value != 0.f)
	{
		//Find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}
