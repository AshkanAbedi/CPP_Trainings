// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CameraBaseSystem.h"
#include "PanningCamera.generated.h"

UCLASS()
class CAMERASYSTEM_API APanningCamera : public ACameraBaseSystem
{
	GENERATED_BODY()

public:
	APanningCamera();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Tracking")
	bool bTrackYaw = true;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Tracking")
	bool bTrackPitch = true;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Tracking", meta = (ClampMin="0.1"))
	float RotationInterpSpeed = 5.0f;

protected:
	virtual void Tick(float DeltaTime) override;
	
private:
	FRotator GetLookAtRotation() const;
};
