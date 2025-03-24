// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "BaseCameraManager.generated.h"

UCLASS()
class CPP_TRAININGS_API ABaseCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()

public:
	
	ABaseCameraManager();

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Cameras)
	TArray<AActor*> CameraViews;
	
};
