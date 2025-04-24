// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseCharacter.h"
#include "BaseMacros.h"
#include "BasePlayerController.h"
#include "Components/ArrowComponent.h"
#include "InputAction.h"
#include "EnhancedInputComponent.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetMesh()->SetWorldLocation(FVector(0,0,-80));
	GetMesh()->SetWorldRotation(FRotator(0,-90, 0));
	GetArrowComponent()->SetHiddenInGame(false);
	GetArrowComponent()->SetVisibility(true);

	AutoPossessPlayer = EAutoReceiveInput::Player0;
	AutoReceiveInput = EAutoReceiveInput::Player0;
	MoveRate = 200.0f;
	TurnRate = 100.0f;
	Velocity = 0.f;

}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	PlayerStates = EPlayerStates::Normal;
}

void ABaseCharacter::MoveForward(const FInputActionInstance& Value)
{
	if (Controller)
	{
		AddMovementInput(GetActorForwardVector());
		bIsWalking = true;
	}
}

void ABaseCharacter::TurnRight(const FInputActionInstance& Value)
{
	if (Controller)
	{
		AddControllerYawInput(GetActorRightVector().GetAbsMax() * TurnRate * GetWorld()->GetDeltaSeconds());
	}
}

void ABaseCharacter::TurnLeft(const FInputActionInstance& Value)
{
	if (Controller)
	{
		AddControllerYawInput(GetActorRightVector().GetAbsMax() * TurnRate * -1.0f * GetWorld()->GetDeltaSeconds());
	}
}

void ABaseCharacter::StopMoving()
{
	Velocity = 0.0f;
	bIsWalking = false;
}

ABasePlayerController* ABaseCharacter::GetPlayerController() const
{
	if (ABasePlayerController* BasePlayerController = Cast<ABasePlayerController>(GetController()))
	{
		return BasePlayerController;
	}
	return nullptr;
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	const double StartTime = FPlatformTime::Seconds();
	
	Super::Tick(DeltaTime);

	///this->AddActorWorldOffset(GetActorForwardVector() * MoveRate * 3.0f * DeltaTime);
	
	const double EndTime = FPlatformTime::Seconds();

	const float DurationMs = (EndTime - StartTime) * 1000.0f;

	PRINT(8, "BaseCharacter Tick took %f ms", Purple, DurationMs);

	const float BudgetPercentage = (DurationMs/16.67f) * 100.0f;

	PRINT(9, "BaseCharacter Tick used %f%% of 16.67ms budget", Purple, BudgetPercentage);

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {

		EnhancedInputComponent->BindAction(InputMoveForward, ETriggerEvent::Triggered, this, &ABaseCharacter::MoveForward);
		EnhancedInputComponent->BindAction(InputMoveForward, ETriggerEvent::Completed, this, &ABaseCharacter::StopMoving);
		EnhancedInputComponent->BindAction(InputTurnRight, ETriggerEvent::Triggered, this, &ABaseCharacter::TurnRight);
		EnhancedInputComponent->BindAction(InputTurnLeft, ETriggerEvent::Triggered, this, &ABaseCharacter::TurnLeft);
	}

}

