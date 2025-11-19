// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "CameraBaseSystem.h"
#include "FixedCamera.generated.h"

UCLASS()
class CAMERASYSTEM_API AFixedCamera : public ACameraBaseSystem
{
	GENERATED_BODY()

public:
	AFixedCamera();
	virtual void OnBecomeActive() override;
	virtual void OnBecomeInactive() override;

protected:


private:


};
