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
	
	PitchFollowSpeed = 0.5f;
	YawFollowSpeed = 0.5f;
	OnCurveSpeed = 0.5f;
	bReverseMovementOnCurve = false;
	
}

void ABaseCamera::BeginPlay()
{
	Super::BeginPlay();
	
	if (!bPitchFollow && !bYawFollow && !bMoveOnCurve)
	{
		PrimaryActorTick.bCanEverTick = false;
		SetActorTickEnabled(false);
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
		MoveOnCurve(DeltaTime);
	}

	if (bYawFollow || bPitchFollow)
	{
		PitchYawFollow(DeltaTime);
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

void ABaseCamera::PitchYawFollow(float DeltaTime) const
{
	const FVector CharacterLocation = PlayerCharacter->GetActorLocation();
	const FVector BoomLocation = SpringArmComponent->GetComponentLocation();
	const FVector DirectionToCharacter = (CharacterLocation - BoomLocation).GetSafeNormal();
	const FRotator TargetRotation = DirectionToCharacter.Rotation();
	const FRotator CurrentRotation = SpringArmComponent->GetComponentRotation();
	float NewPitch = CurrentRotation.Pitch;
	float NewYaw = CurrentRotation.Yaw;

	if (bPitchFollow)
	{
		NewPitch = FMath::FInterpTo(CurrentRotation.Pitch, TargetRotation.Pitch, DeltaTime, PitchFollowSpeed);
		NewPitch = FMath::Clamp(NewPitch, -91.0f, 91.0f);
		PRINT(1, "Camera Pitch: %f", Green, NewPitch);
	}

	if (bYawFollow)
	{
		float DeltaYaw = TargetRotation.Yaw - CurrentRotation.Yaw;
		if (DeltaYaw >= 180.0f)
		{
			DeltaYaw -= 360.0f;
		}
		else if (DeltaYaw <= -180.0f)
		{
			DeltaYaw += 360.0f;
		}
		NewYaw = CurrentRotation.Yaw + FMath::FInterpTo(0.0f, DeltaYaw, DeltaTime, YawFollowSpeed);
		NewYaw = FMath::Clamp(NewYaw, -181.0f, 181.0f);
		PRINT(2, "Camera Yaw: %f", Green, NewYaw);
	}

	const FRotator NewRotation(NewPitch, NewYaw, CurrentRotation.Roll);
	SpringArmComponent->SetWorldRotation(NewRotation);
}

void ABaseCamera::MoveOnCurve(float DeltaTime)
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
		const float DirectionalScale = bReverseMovementOnCurve ? -1.0f : 1.0f;
		const float DeltaDistance = VelocityComponentAlongSpline * DirectionalScale * OnCurveSpeed * DeltaTime;
		const float CurrentDistance = SplineComponent->GetDistanceAlongSplineAtSplineInputKey(CurrentPositionOnSpline);
		const float TargetDistance = CurrentDistance + DeltaDistance;
		const float TargetSplineInputKey = SplineComponent->GetInputKeyAtDistanceAlongSpline(TargetDistance);

		CurrentPositionOnSpline = FMath::FInterpTo(CurrentPositionOnSpline, TargetSplineInputKey, DeltaTime, OnCurveSpeed);
		CurrentPositionOnSpline = FMath::Clamp(CurrentPositionOnSpline, 0.0f, 1.0f);
		const FVector NewLocOnSpline = SplineComponent->GetLocationAtSplineInputKey(CurrentPositionOnSpline, ESplineCoordinateSpace::World);
		SpringArmComponent->SetWorldLocation(NewLocOnSpline);
	}
}





