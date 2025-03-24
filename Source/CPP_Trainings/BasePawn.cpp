// Fill out your copyright notice in the Description page of Project Settings.

#include "BasePawn.h"
#include "Public/BaseMacros.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));

	RootComponent = SceneComponent;

	BaseSkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Base Skeletal Mesh"));
	BaseSkeletalMesh->SetupAttachment(RootComponent);

	BaseSkeletalMesh->SetWorldRotation(FRotator(0.f, -90.f, 0.f));

	ForwardArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Forward Arrow"));
	ForwardArrow->SetupAttachment(RootComponent);
	
	ForwardArrow->SetHiddenInGame(false);
	
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	SpeedMultiplier = 200.f;
	TurnRate = 100.f;
	
}

// Called when the game starts or when spawned
void ABasePawn::BeginPlay()
{
	Super::BeginPlay();
	PlayerStates = EPlayerStates::Normal;
}


void ABasePawn::MoveForward(const FInputActionInstance& Value)
{
	if (const float InputValue = Value.GetValue().Get<float>(); InputValue != 0)
	{
		const FVector ForwardVector = FVector(1, 0, 0);
		const float DeltaTime = GetWorld()->GetDeltaSeconds();
		const FVector DeltaLocation = ForwardVector * InputValue * SpeedMultiplier * DeltaTime;
		Velocity =+ DeltaLocation.Size() / DeltaTime; 
		AddActorLocalOffset(DeltaLocation);
		PlayerStates = EPlayerStates::Walking;
		PRINT(4, "Delta Location Size: %f", Purple, DeltaLocation.Size());
	}
}

void ABasePawn::Turn(const FInputActionInstance& Value)
{
	const float DeltaTime = GetWorld()->GetDeltaSeconds();
	
	const FRotator DeltaRotation = FRotator(0.f, Value.GetValue().Get<float>() * TurnRate * DeltaTime, 0.f);
	
	this->AddActorWorldRotation(DeltaRotation);
	
}

void ABasePawn::StopMoving()
{
	Velocity = 0.f;
}

// Called every frame
void ABasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	PRINT(5, "Location: %s, Rotation: %s", Green, *GetActorLocation().ToString(), *GetActorRotation().ToString());
	PRINT(6, "Velocity: %f", Purple, Velocity);
}

// Called to bind functionality to input
void ABasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {

		PRINT(7, "Enhanced Input Component Found", Green);

		EnhancedInputComponent->BindAction(InputMoveForward, ETriggerEvent::Triggered, this, &ABasePawn::MoveForward);
		EnhancedInputComponent->BindAction(InputMoveForward, ETriggerEvent::Completed, this, &ABasePawn::StopMoving);
		EnhancedInputComponent->BindAction(InputTurnRight, ETriggerEvent::Triggered, this, &ABasePawn::Turn);
	}

}

void ABasePawn::CastRecognition()
{
	PRINT(8, "Hello, Your Pawn is Here!", Green);
}


