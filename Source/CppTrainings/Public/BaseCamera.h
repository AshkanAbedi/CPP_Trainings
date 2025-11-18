// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "BaseCamera.generated.h"

class USpringArmComponent;
class USplineComponent;
class ABaseCharacter;

UCLASS()
class CPPTRAININGS_API ABaseCamera : public ACameraActor
{
	GENERATED_BODY()

public:
	ABaseCamera();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Component)
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Component)
	TObjectPtr<USplineComponent> SplineComponent;
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void BecomeViewTarget(APlayerController* PC) override;
	virtual void EndViewTarget(APlayerController* PC) override;
	void PitchYawFollow(float DeltaTime) const;
	void MoveOnCurve(float DeltaTime);
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Behavior)
	bool bPitchFollow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Behavior)
	bool bYawFollow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Behavior)
	bool bMoveOnCurve;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Behavior)
	bool bReverseMovementOnCurve;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Behavior)
	float PitchFollowSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Behavior)
	float YawFollowSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Behavior)
	float OnCurveSpeed;

protected:

	UPROPERTY()
	TObjectPtr<ABaseCharacter> PlayerCharacter;
	
	FVector CameraOriginalPosition;

	FRotator CameraOriginalRotation;
	
	float CurrentPositionOnSpline;
	
};
