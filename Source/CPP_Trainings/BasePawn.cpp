// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/BaseMacros.h"
#include "BasePawn.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseSkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Base Skeletal Mesh"));
	BaseSkeletalMesh->SetupAttachment(RootComponent);

	BaseSkeletalMesh->SetWorldRotation(FRotator(0.f, -90.0f, 0.f));

	ForwardArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Forward Arrow"));
	ForwardArrow->SetupAttachment(BaseSkeletalMesh);
	
	ForwardArrow->SetWorldRotation(FRotator(0.f, 90.f, 0.f));
	ForwardArrow->SetHiddenInGame(false);

	BaseCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Base Camera"));
	BaseCamera->SetupAttachment(BaseSkeletalMesh);

	MoveSpeed = 150.f;

	AutoPossessPlayer = EAutoReceiveInput::Player0;
	
}

// Called when the game starts or when spawned
void ABasePawn::BeginPlay()
{
	Super::BeginPlay();
	//PlayerStates = EPlayerStates::Normal;
}


void ABasePawn::MoveForward(const FInputActionInstance& Value)
{
	float InputValue = Value.GetValue().Get<float>();
	
	if (InputValue != 0)
	{
		//AddMovementInput(ForwardArrow->GetForwardVector(), InputValue * MoveSpeed);
		AddActorLocalOffset(GetActorForwardVector() * InputValue * MoveSpeed * GetWorld()->GetDeltaSeconds());
		//PlayerStates = EPlayerStates::Walking;
	}
}

void ABasePawn::TurnRight(const FInputActionInstance& Value)
{
	if (PlayerStates == EPlayerStates::Normal || PlayerStates == EPlayerStates::Walking)
	{
		AddControllerYawInput(Value.GetElapsedTime());
	}
}

void ABasePawn::TurnLeft(const FInputActionInstance& Value)
{
	if (PlayerStates == EPlayerStates::Normal || PlayerStates == EPlayerStates::Walking)
	{
		AddControllerPitchInput(Value.GetElapsedTime());
	}
}

// Called every frame
void ABasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	PRINT("Location: %s, Rotation: %s", Green, *GetActorLocation().ToString(), *GetActorRotation().ToString());
}

// Called to bind functionality to input
void ABasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {

		EnhancedInputComponent->BindAction(InputMoveForward, ETriggerEvent::Triggered, this, &ABasePawn::MoveForward);
		EnhancedInputComponent->BindAction(InputTurnRight, ETriggerEvent::Triggered, this, &ABasePawn::TurnRight);
		EnhancedInputComponent->BindAction(InputTurnLeft, ETriggerEvent::Triggered, this, &ABasePawn::TurnLeft);

	}

}

