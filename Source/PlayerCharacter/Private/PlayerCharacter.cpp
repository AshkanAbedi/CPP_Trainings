// Fill out your copyright notice in the Description page of Project Settings.
// ReSharper disable CppTooWideScopeInitStatement
#include "PlayerCharacter.h"
#include "Components/ArrowComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"

DEFINE_LOG_CATEGORY(LogPlayerCharacter);

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	GetMesh()->SetWorldLocation(FVector(0,0,-80));
	GetMesh()->SetWorldRotation(FRotator(0,-90, 0));
	
#if WITH_EDITOR
	GetArrowComponent()->SetHiddenInGame(false);
	GetArrowComponent()->SetVisibility(true);
#endif
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	GetCharacterMovement()->bOrientRotationToMovement = false;
	
	TurnRate = 100.0f;
	
	GetCapsuleComponent()->SetHiddenInGame(false);
	GetCapsuleComponent()->SetGenerateOverlapEvents(true);
	GetCapsuleComponent()->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Ignore);

}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (InputMoveForward)
		{
			EnhancedInputComponent->BindAction(InputMoveForward, ETriggerEvent::Triggered, this, &APlayerCharacter::MoveForward);
		}
		if (InputTurn)
		{
			EnhancedInputComponent->BindAction(InputTurn, ETriggerEvent::Triggered, this, &APlayerCharacter::Turn);
		}
	}
}

void APlayerCharacter::MoveForward(const FInputActionValue& Value)
{
	float MovementValue = Value.Get<float>();
	
	if (GetController() != nullptr && MovementValue != 0.f)
	{
		const FVector Forward = GetActorForwardVector();
		AddMovementInput(Forward, MovementValue * MoveRate);
		//GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Green, FString::Printf(TEXT("MoveForward: %f"), MovementValue));
	}
}

void APlayerCharacter::Turn(const FInputActionValue& Value)
{
	const float TurnValue = Value.Get<float>();
	
	if (GetController() != nullptr && TurnValue != 0)
	{
		const float TurnAmount = TurnValue * TurnRate * GetWorld()->GetDeltaSeconds();
		AddActorLocalRotation(FRotator(0.f, TurnAmount, 0.f));
	}
}


