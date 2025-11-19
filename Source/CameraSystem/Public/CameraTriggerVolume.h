// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CameraTriggerVolume.generated.h"

class ACameraBaseSystem;
class UBoxComponent;
class UStaticMeshComponent;

UCLASS(Blueprintable, BlueprintType)
class CAMERASYSTEM_API ACameraTriggerVolume : public AActor
{
	GENERATED_BODY()

public:
	ACameraTriggerVolume();

protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UBoxComponent> TriggerVolume;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;
	
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
