// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "CameraRig_Rail.h"
#include "BaseCameraRail.generated.h"

class UChildActorComponent;

UCLASS()
class CPP_TRAININGS_API ABaseCameraRail : public ACameraRig_Rail
{
	GENERATED_BODY()

public:
	explicit ABaseCameraRail(const FObjectInitializer& ObjectInitializer);
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	TObjectPtr<UChildActorComponent> CameraActorComponent;

	float MoveSpeed = 0.2f;
	bool bIsMoving = false;
	
};
