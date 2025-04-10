// Fill out your copyright notice in the Description page of Project Settings.
// ReSharper disable CppMemberFunctionMayBeStatic
// ReSharper disable CppParameterMayBeConstPtrOrRef
#include "BaseCamera.h"
#include "BaseMacros.h"
#include "GameFramework/SpringArmComponent.h"
#include "BaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"

ABaseCamera::ABaseCamera()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));

	RootComponent = SpringArmComponent;

	GetCameraComponent()->SetupAttachment(SpringArmComponent);
	
}

void ABaseCamera::BeginPlay()
{
	Super::BeginPlay();
	
	if (!bFollowCharacter)
	{
		PrimaryActorTick.bCanEverTick = false;
	}
	
	PlayerCharacter = Cast<ABaseCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

void ABaseCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (bFollowCharacter)
	{
		PitchUpdate(DeltaTime);	
	}
}

void ABaseCamera::PitchUpdate(float DeltaTime)
{
		// Get the root bone's world location
	const FVector CharacterLocation = PlayerCharacter->GetActorLocation();

			// Camera's fixed location
	const FVector BoomLocation = SpringArmComponent->GetComponentLocation();

			// Direction from camera to root bone
	const FVector DirectionToBone = (CharacterLocation - BoomLocation).GetSafeNormal();

			// Convert direction to rotation
	const FRotator TargetRotation = DirectionToBone.Rotation();

			// Get current rotation
	const FRotator CurrentRotation = SpringArmComponent->GetComponentRotation();

	float DeltaYaw = TargetRotation.Yaw - CurrentRotation.Yaw;
	
	if (DeltaYaw > 180.0f)
	{
		DeltaYaw -= 360.0f;
	} else if (DeltaYaw < -180.f)
	{
		DeltaYaw += 360.0f;
	}

			// Smoothly interpolate pitch and yaw (ignore roll)
	constexpr float AdjustmentSpeed = 2.0f; // Smoothness factor
	const float NewPitch = FMath::FInterpTo(CurrentRotation.Pitch, TargetRotation.Pitch, DeltaTime, AdjustmentSpeed);
	const float NewYaw = CurrentRotation.Yaw + FMath::FInterpTo(0.0f, DeltaYaw, DeltaTime, AdjustmentSpeed);

			// Clamp pitch to reasonable bounds
	const float ClampedPitch = FMath::Clamp(NewPitch, -90.0f, 90.0f);
	const float ClampedYaw = FMath::Clamp(NewYaw, -180.0f, 180.0f);

			// Apply new rotation (keep roll unchanged)
	const FRotator NewRotation(ClampedPitch, ClampedYaw, CurrentRotation.Roll);
	SpringArmComponent->SetWorldRotation(NewRotation);

	PRINT(1, "BoomPitch: %f", Green, SpringArmComponent->GetComponentRotation().Pitch);
	PRINT(2, "BoomYaw: %f", Green, SpringArmComponent->GetComponentRotation().Yaw);
	
}

