// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "BaseCamera.generated.h"

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

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	void PitchUpdate(float DeltaTime);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Behavior)
	bool bFollowCharacter;
	
	UPROPERTY()
	ABaseCharacter* PlayerCharacter;
	float OriginalPitch;
	FTimerHandle PitchUpdateTimerHandle;
protected:
	
};
