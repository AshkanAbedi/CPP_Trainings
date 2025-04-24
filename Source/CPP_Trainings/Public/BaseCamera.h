// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "BaseCamera.generated.h"

class USpringArmComponent;
class USplineComponent;
class ABaseCharacter;

UCLASS()
class CPP_TRAININGS_API ABaseCamera : public ACameraActor
{
	GENERATED_BODY()

public:
	ABaseCamera();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Component)
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Component)
	TObjectPtr<USplineComponent> SplineComponent;

	/*UFUNCTION()
	void OnActivated(UActorComponent* Component, bool bReset);*/
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void BecomeViewTarget(APlayerController* PC) override;
	virtual void EndViewTarget(APlayerController* PC) override;
	void PitchYawUpdate(float DeltaTime) const;
	void MoveOnSpline(float DeltaTime);
	// void MoveOnCurve(float DeltaTime);
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Behavior)
	bool bFollowCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Behavior)
	bool bMoveOnCurve;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Behavior)
	bool bReverseMovementOnSpline;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Behavior)
	float AdjustmentSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Behavior)
	float SpeedOnSpline;

	FVector CameraOriginalPosition;

	FRotator CameraOriginalRotation;
	
	float CurrentPositionOnSpline;
	
	UPROPERTY()
	ABaseCharacter* PlayerCharacter;

protected:
	
};
