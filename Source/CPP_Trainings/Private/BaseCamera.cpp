// Fill out your copyright notice in the Description page of Project Settings.
// ReSharper disable CppMemberFunctionMayBeStatic
// ReSharper disable CppParameterMayBeConstPtrOrRef
#include "BaseCamera.h"
#include "BaseMacros.h"
#include "BaseCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SplineComponent.h"
#include "Kismet/GameplayStatics.h"

ABaseCamera::ABaseCamera()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->TargetArmLength = 10.0f;
	GetCameraComponent()->SetupAttachment(SpringArmComponent);

	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("Spline Component"));
	SplineComponent->SetupAttachment(RootComponent);
	
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

	// Find closest point on spline to character
	const float InputKey = SplineComponent->FindInputKeyClosestToWorldLocation(PlayerCharacter->GetActorLocation());
	const FVector ClosestPoint = SplineComponent->GetLocationAtSplineInputKey(InputKey, ESplineCoordinateSpace::World);

	// Calculate distance
	const float Distance = FVector::Distance(PlayerCharacter->GetActorLocation(), ClosestPoint);

	// Normalize distance (0 = at spline, 1 = MaxDistance)
	const float NormalizedDistance = FMath::Clamp(Distance / 10000.0f, 0.0f, 1.0f);

	// Invert to increase position when closer (close → 1, far → 0)
	const float Influence = 1.0f - NormalizedDistance;

	// Adjust CurrentPositionOnSpline
	//CurrentPositionOnSpline += Influence * SpeedOnSpline * DeltaTime;
	CurrentPositionOnSpline = FMath::Clamp(Influence, 0.0f, 1.0f);

	// Move spring arm along spline
	const FVector NewLocOnSpline = SplineComponent->GetLocationAtSplineInputKey(Influence, ESplineCoordinateSpace::World);
	SpringArmComponent->SetWorldLocation(NewLocOnSpline);

	PRINT(0, "(Current Position on Spline: %s)", Green, *NewLocOnSpline.ToString());
	
	if (bFollowCharacter)
	{
		PitchYawUpdate(DeltaTime);	
	}
}

void ABaseCamera::PitchYawUpdate(float DeltaTime) const
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

	const float ClampedPitch = FMath::Clamp(NewPitch, -91.0f, 91.0f);
	const float ClampedYaw = FMath::Clamp(NewYaw, -181.0f, 181.0f);

	const FRotator NewRotation(ClampedPitch, ClampedYaw, CurrentRotation.Roll);
	SpringArmComponent->SetWorldRotation(NewRotation);

	PRINT(1, "BoomPitch: %f", Green, SpringArmComponent->GetComponentRotation().Pitch);
	PRINT(2, "BoomYaw: %f", Green, SpringArmComponent->GetComponentRotation().Yaw);
	
}

