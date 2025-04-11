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
		PitchYawUpdate(DeltaTime);	
	}
}

void ABaseCamera::PitchYawUpdate(float DeltaTime)
{
	const FVector CharacterLocation = PlayerCharacter->GetActorLocation();
	
	const FVector BoomLocation = SpringArmComponent->GetComponentLocation();
	
	const FVector DirectionToCharacter = (CharacterLocation - BoomLocation).GetSafeNormal();

	const FRotator TargetRotation = DirectionToCharacter.Rotation();

	const FRotator CurrentRotation = SpringArmComponent->GetComponentRotation();

	float DeltaYaw = TargetRotation.Yaw - CurrentRotation.Yaw;
	
	if (DeltaYaw >= 180.0f)
	{
		DeltaYaw -= 360.0f;
	} else if (DeltaYaw <= -180.f)
	{
		DeltaYaw += 360.0f;
	}

	constexpr float AdjustmentSpeed = 2.0f;
	const float NewPitch = FMath::FInterpTo(CurrentRotation.Pitch, TargetRotation.Pitch, DeltaTime, AdjustmentSpeed);
	const float NewYaw = CurrentRotation.Yaw + FMath::FInterpTo(0.0f, DeltaYaw, DeltaTime, AdjustmentSpeed);

	const float ClampedPitch = FMath::Clamp(NewPitch, -90.0f, 90.0f);
	const float ClampedYaw = FMath::Clamp(NewYaw, -181.0f, 181.0f);

	const FRotator NewRotation(ClampedPitch, ClampedYaw, CurrentRotation.Roll);
	SpringArmComponent->SetWorldRotation(NewRotation);

	PRINT(1, "BoomPitch: %f", Green, SpringArmComponent->GetComponentRotation().Pitch);
	PRINT(2, "BoomYaw: %f", Green, SpringArmComponent->GetComponentRotation().Yaw);
	
}

