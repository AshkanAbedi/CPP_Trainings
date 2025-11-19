// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerVolume.h"
#include "CameraTriggerVolume.generated.h"

class ACameraBaseSystem;

UCLASS()
class CAMERASYSTEM_API ACameraTriggerVolume : public ATriggerVolume
{
	GENERATED_BODY()

public:
	ACameraTriggerVolume();

protected:
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Camera System")
	TSoftObjectPtr<ACameraBaseSystem> CameraToActivate;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera System")
	int32 Priority = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera System")
	float BlendTime = 0.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera System")
	float BlendExp = 2.0f;
	
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

private:

};
