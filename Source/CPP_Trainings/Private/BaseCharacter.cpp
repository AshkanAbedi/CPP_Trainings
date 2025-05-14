// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseMacros.h"
#include "BaseCharacter.h"
#include "BasePlayerController.h"
#include "Components/ArrowComponent.h"
#include "Components/CapsuleComponent.h"
#include "BaseAbilitySystemComponent.h"
#include "BaseAttributeSet.h"
#include "BaseStairActor.h"
#include "InputAction.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ABaseCharacter::ABaseCharacter()
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
	
	BaseAbilitySystemComponent = CreateDefaultSubobject<UBaseAbilitySystemComponent>(TEXT("BaseAbilitySystemComponent"));
	BaseAttributeSet = CreateDefaultSubobject<UBaseAttributeSet>(TEXT("BaseAttributeSet"));

	AutoPossessPlayer = EAutoReceiveInput::Player0;
	AutoReceiveInput = EAutoReceiveInput::Player0;

	CollisionParams.AddIgnoredActor(this);
	CollisionParams.bTraceComplex = true;

	DefaultWalkSpeed = 200.0f;
	OnStairsSpeed = 50.0f;
	TurnRate = 100.0f;
	Velocity = 0.0f;

	bIsWalking = false;
	bIsOnStair = false;
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(InputMappingContext && InputMoveForward && InputTurnRight && InputTurnLeft);

	if (BaseAbilitySystemComponent)
		BaseAbilitySystemComponent->InitAbilityActorInfo(this, this);

	PlayerStates = EPlayerStates::Normal;
	GetCharacterMovement()->MaxWalkSpeed = DefaultWalkSpeed;
	
	//GetWorld()->GetTimerManager().SetTimer(TraceTimerHandle, this, &ABaseCharacter::Tracing, 0.1f, true);
}

UAbilitySystemComponent* ABaseCharacter::GetAbilitySystemComponent() const
{
	return BaseAbilitySystemComponent;
}

void ABaseCharacter::MoveForward(const FInputActionInstance& Value)
{
	if (Controller && GetWorld())
	{
		const float ScaleValue = Value.GetValue().Get<float>();
		AddMovementInput(GetActorForwardVector(), ScaleValue);
		bIsWalking = ScaleValue > 0.0f;
		UpdatePlayerState();
	}
}

void ABaseCharacter::TurnRight(const FInputActionInstance& Value)
{
	if (Controller && GetWorld())
	{
		AddControllerYawInput(GetActorRightVector().GetAbsMax() * TurnRate * GetWorld()->GetDeltaSeconds());
	}
}

void ABaseCharacter::TurnLeft(const FInputActionInstance& Value)
{
	if (Controller && GetWorld())
	{
		AddControllerYawInput(GetActorRightVector().GetAbsMax() * TurnRate * -1.0f * GetWorld()->GetDeltaSeconds());
	}
}

void ABaseCharacter::StopMoving()
{
	bIsWalking = false;
	UpdatePlayerState();
}

ABasePlayerController* ABaseCharacter::GetPlayerController() const
{
	return Cast<ABasePlayerController>(GetController());
}

#if UE_BUILD_DEBUG
void ABaseCharacter::StatFPS()
{
	const double StartTime = FPlatformTime::Seconds();
	
	const double EndTime = FPlatformTime::Seconds();

	const float DurationMs = (EndTime - StartTime) * 1000.0f;

	PRINT(8, "BaseCharacter Tick took %f ms", Purple, DurationMs);

	const float BudgetPercentage = (DurationMs/16.67f) * 100.0f;

	PRINT(9, "BaseCharacter Tick used %f%% of 16.67ms budget", Purple, BudgetPercentage);
}
#endif


void ABaseCharacter::Tracing()
{
	if (!GetWorld())
		return;
	
	const FVector TraceStartPoint = GetMesh()->GetBoneLocation(TEXT("Pelvis"));
	
	const FVector TraceEndPoint = TraceStartPoint + (FVector(0, 0, -1) * 500.0f);

	const bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, TraceStartPoint, TraceEndPoint, ECC_Visibility,
	                                                     CollisionParams);

	if (bHit && HitResult.GetActor())
	{
		PRINT(10, "Hit Actor: %s", Green, *HitResult.GetActor()->GetName());

		if (HitResult.GetActor()->IsA(ABaseStairActor::StaticClass()))
		{
			bIsOnStair = true;
			UpdatePlayerState();
			GetCharacterMovement()->MaxWalkSpeed = 50.f;
		}

		else
		{
			bIsOnStair = false;
			UpdatePlayerState();
			GetCharacterMovement()->MaxWalkSpeed = 200.f;
		}
	}

	//DrawDebugLine(GetWorld(), TraceStartPoint, TraceEndPoint, FColor::Red, false, 1.0f, 0, 1.0f);
}

void ABaseCharacter::SetIsOnStairs(bool bNewIsOnStairs)
{
	if (bIsOnStair != bNewIsOnStairs)
	{
		bIsOnStair = bNewIsOnStairs;
		GetCharacterMovement()->MaxWalkSpeed = bIsOnStair ? OnStairsSpeed : DefaultWalkSpeed;
		UpdatePlayerState();
	}
}

void ABaseCharacter::UpdatePlayerState()
{
	PlayerStates = bIsOnStair ? EPlayerStates::OnStairs : (bIsWalking ? EPlayerStates::Walking : EPlayerStates::Normal);
	SetActorTickEnabled(bIsOnStair || bIsWalking);
}

void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

#if UE_BUILD_DEBUG
	StatFPS();
#endif
	
}

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

