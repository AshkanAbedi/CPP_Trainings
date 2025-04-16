// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "BaseCamera.generated.h"

class USplineComponent;
class ABaseCharacter;
class USpringArmComponent;

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

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	void PitchYawUpdate(float DeltaTime) const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Behavior)
	bool bFollowCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Behavior)
	float SpeedOnSpline = 0.2f;

	float CurrentPositionOnSpline  = 0.0f;
	
	UPROPERTY()
	ABaseCharacter* PlayerCharacter;

protected:
	
};
