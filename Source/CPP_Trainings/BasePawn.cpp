// Fill out your copyright notice in the Description page of Project Settings.

#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "EnhancedInputComponent.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Component"));
	RootComponent = CapsuleComponent;

	BaseSkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Base Skeletal Mesh"));
	BaseSkeletalMesh->SetupAttachment(RootComponent);

	BaseCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Base Camera"));
	BaseCamera->SetupAttachment(RootComponent);

	AutoReceiveInput = EAutoReceiveInput::Player0;
	
}

// Called when the game starts or when spawned
void ABasePawn::BeginPlay()
{
	Super::BeginPlay();
	PlayerStates = EPlayerStates::Normal;
}


void ABasePawn::MoveForward(const FInputActionValue& Value)
{
	if (PlayerStates == EPlayerStates::Normal)
	{
		AddMovementInput(this->GetActorForwardVector(), Value.GetMagnitude());
		PlayerStates = EPlayerStates::Walking;
	}
}

void ABasePawn::TurnRight(const FInputActionValue& Value)
{
	if (PlayerStates == EPlayerStates::Normal || PlayerStates == EPlayerStates::Walking)
	{
		AddControllerYawInput(Value.GetMagnitude());
	}
}

void ABasePawn::TurnLeft(const FInputActionValue& Value)
{
	if (PlayerStates == EPlayerStates::Normal || PlayerStates == EPlayerStates::Walking)
	{
		AddControllerPitchInput(Value.GetMagnitude());
	}
}

// Called every frame
void ABasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	EnhancedInputComponent->BindAction(InputMoveForward, ETriggerEvent::Triggered, this, &ABasePawn::MoveForward);
	EnhancedInputComponent->BindAction(InputTurnRight, ETriggerEvent::Triggered, this, &ABasePawn::TurnRight);
	EnhancedInputComponent->BindAction(InputTurnLeft, ETriggerEvent::Triggered, this, &ABasePawn::TurnLeft);

}

