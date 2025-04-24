// Fill out your copyright notice in the Description page of Project Settings.
// ReSharper disable CppMemberFunctionMayBeStatic
// ReSharper disable CppParameterMayBeConstPtrOrRef
// ReSharper disable CppMemberFunctionMayBeConst

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
	
	AdjustmentSpeed = 0.5f;
	SpeedOnSpline = 0.5f;
	bReverseMovementOnSpline = false;
	
}


void ABaseCamera::BeginPlay()
{
	Super::BeginPlay();
	
	if (!bFollowCharacter || !bMoveOnCurve)
	{
		PrimaryActorTick.bCanEverTick = false;
	}

	CameraOriginalPosition = GetActorLocation();
	CameraOriginalRotation = GetActorRotation();
	
	PlayerCharacter = Cast<ABaseCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (IsValid(PlayerCharacter) && IsValid(SplineComponent) && SplineComponent->GetNumberOfSplinePoints() > 0)
	{
		const FVector FirstPointPos = SplineComponent->GetLocationAtSplinePoint(0, ESplineCoordinateSpace::World);
		SpringArmComponent->SetWorldLocation(FirstPointPos);
		CurrentPositionOnSpline = 0.0f;
	}
}

void ABaseCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (bMoveOnCurve)
	{
		MoveOnSpline(DeltaTime);
	}
	
	if (bFollowCharacter)
	{
		PitchYawUpdate(DeltaTime);	
	}
}

void ABaseCamera::BecomeViewTarget(APlayerController* PC)
{
	Super::BecomeViewTarget(PC);
	PRINT(10, "Camera Number: %s is the view target" , Green, *this->GetName());
	SetActorLocation(CameraOriginalPosition);
	SetActorRotation(CameraOriginalRotation);
}

void ABaseCamera::EndViewTarget(APlayerController* PC)
{
	Super::EndViewTarget(PC);
	PRINT(11, "Camera Number: %p is off" , Green, this);
	SetActorLocation(CameraOriginalPosition);
	SetActorRotation(CameraOriginalRotation);
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
	
	const float NewPitch = FMath::FInterpTo(CurrentRotation.Pitch, TargetRotation.Pitch, DeltaTime, AdjustmentSpeed);
	const float NewYaw = CurrentRotation.Yaw + FMath::FInterpTo(0.0f, DeltaYaw, DeltaTime, AdjustmentSpeed);

	const float ClampedPitch = FMath::Clamp(NewPitch, -91.0f, 91.0f);
	const float ClampedYaw = FMath::Clamp(NewYaw, -181.0f, 181.0f);

	const FRotator NewRotation(ClampedPitch, ClampedYaw, CurrentRotation.Roll);
	SpringArmComponent->SetWorldRotation(NewRotation);

	PRINT(1, "BoomPitch: %f", Green, SpringArmComponent->GetComponentRotation().Pitch);
	PRINT(2, "BoomYaw: %f", Green, SpringArmComponent->GetComponentRotation().Yaw);
	
}

void ABaseCamera::MoveOnSpline(float DeltaTime)
{

	if (!IsValid(PlayerCharacter) || !IsValid(SplineComponent))
	{
		return;
	}

	if (bool bIsPlayerMoving = PlayerCharacter->GetVelocity().SizeSquared() > 100.0f)
	{
		const FVector PlayerVelocity = PlayerCharacter->GetVelocity();
		const FVector SplineTangent = SplineComponent->GetTangentAtSplineInputKey(CurrentPositionOnSpline, ESplineCoordinateSpace::World);
		const float VelocityComponentAlongSpline = FVector::DotProduct(PlayerVelocity, SplineTangent);
		const float DirectionalScale = bReverseMovementOnSpline ? -1.0f : 1.0f;
		const float DeltaDistance = VelocityComponentAlongSpline * DirectionalScale * SpeedOnSpline * DeltaTime;
		const float CurrentDistance = SplineComponent->GetDistanceAlongSplineAtSplineInputKey(CurrentPositionOnSpline);
		const float TargetDistance = CurrentDistance + DeltaDistance;
		const float TargetSplineInputKey = SplineComponent->GetInputKeyAtDistanceAlongSpline(TargetDistance);

		CurrentPositionOnSpline = FMath::FInterpTo(CurrentPositionOnSpline, TargetSplineInputKey, DeltaTime, SpeedOnSpline);
		CurrentPositionOnSpline = FMath::Clamp(CurrentPositionOnSpline, 0.0f, 1.0f);
		const FVector NewLocOnSpline = SplineComponent->GetLocationAtSplineInputKey(CurrentPositionOnSpline, ESplineCoordinateSpace::World);
		SpringArmComponent->SetWorldLocation(NewLocOnSpline);
		
		// float InputKey = SplineComponent->FindInputKeyClosestToWorldLocation(PlayerCharacter->GetActorLocation());
		// InputKey = FMath::Clamp(InputKey, 0.0f, 1.0f);
		//
		// CurrentPositionOnSpline = FMath::FInterpTo(CurrentPositionOnSpline, InputKey, DeltaTime, SpeedOnSpline);
		// CurrentPositionOnSpline = FMath::Clamp(CurrentPositionOnSpline, 0.0f, 1.0f);
		//
		// const FVector NewLocOnSpline = SplineComponent->GetLocationAtSplineInputKey(CurrentPositionOnSpline, ESplineCoordinateSpace::World);
		// SpringArmComponent->SetWorldLocation(NewLocOnSpline);
	}
}

// void ABaseCamera::MoveOnCurve(float DeltaTime)
// {
// 	if (!IsValid(PlayerCharacter) || !IsValid(SplineComponent)) return;
// 	
// 	const FVector FirstSplinePoint = SplineComponent->GetLocationAtSplinePoint(1, ESplineCoordinateSpace::World);
// 	const FVector LastSplinePoint = SplineComponent->GetLocationAtSplinePoint(0, ESplineCoordinateSpace::World);
//
// 	const FVector CurrentPlayerLocation = PlayerCharacter->GetActorLocation();
// 	
// 	const float DistanceToFirstPoint = FVector::Distance(CurrentPlayerLocation, FirstSplinePoint);
// 	const float DistanceToLastPoint = FVector::Distance(CurrentPlayerLocation, LastSplinePoint);
// 	
// 	const float TotalDistance = DistanceToFirstPoint + DistanceToLastPoint;
// 	float NewPositionOnSpline = 0.0f;
//
// 	if (TotalDistance > 0.0f)
// 	{
// 		NewPositionOnSpline = DistanceToFirstPoint / TotalDistance;
// 		NewPositionOnSpline = FMath::Clamp(NewPositionOnSpline, 0.0f, 1.0f);
// 		NewPositionOnSpline = 1.0f - NewPositionOnSpline;
// 	}
//
// 	CurrentPositionOnSpline = FMath::FInterpTo(CurrentPositionOnSpline, NewPositionOnSpline, DeltaTime, SpeedOnSpline);
// 	CurrentPositionOnSpline = FMath::Clamp(CurrentPositionOnSpline, 0.0f, 1.0f);
// 	
// 	const FVector NewLocationForCamera = SplineComponent->GetLocationAtSplineInputKey(CurrentPositionOnSpline, ESplineCoordinateSpace::World);
// 	SpringArmComponent->SetWorldLocation(NewLocationForCamera);
//
// 	PRINT(0, "(Current Position on Spline: %f)", Green, CurrentPositionOnSpline);
// }




