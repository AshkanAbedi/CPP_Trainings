// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "CameraBaseSystem.generated.h"

UCLASS(Abstract)
class CAMERASYSTEM_API ACameraBaseSystem : public ACameraActor
{
	GENERATED_BODY()

public:
	ACameraBaseSystem();
	virtual void OnBecomeActive();
	virtual void OnBecomeInactive();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	
};
