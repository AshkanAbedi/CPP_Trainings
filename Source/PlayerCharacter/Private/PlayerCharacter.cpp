// Fill out your copyright notice in the Description page of Project Settings.
#include "PlayerCharacter.h"
#include "InputActionValue.h"
#include "Components/ArrowComponent.h"
#include "Components/CapsuleComponent.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	GetMesh()->SetWorldLocation(FVector(0,0,-80));
	GetMesh()->SetWorldRotation(FRotator(0,-90, 0));
	GetArrowComponent()->SetHiddenInGame(false);
	GetArrowComponent()->SetVisibility(true);
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
}

void APlayerCharacter::MoveForward(const FInputActionValue& Value)
{
	const FVector2D MoveVector = Value.Get<FVector2D>();
	if (GetController() != nullptr)
	{
		const FVector Forward = GetActorForwardVector();
		const FVector Right = GetActorRightVector();
		AddMovementInput(Forward, MoveVector.Y);
		//AddMovementInput(Right, MoveVector.X);
		GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Green, FString::Printf(TEXT("Move X: %f Y: %f"), MoveVector.X, MoveVector.Y));
	}
}

void APlayerCharacter::Turn(const FInputActionValue& Value)
{
	if (Controller && GetWorld())
	{
		AddControllerYawInput(GetActorRightVector().GetAbsMax() * TurnRate * GetWorld()->GetDeltaSeconds());
	}
}


