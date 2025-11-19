// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "CameraDirectorSubsystem.generated.h"

class ACameraBaseSystem;

UCLASS()
class CAMERASYSTEM_API UCameraDirectorSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	
	UFUNCTION(BlueprintCallable, Category = "Camera System")
	void RequestCameraChange(TSoftObjectPtr<ACameraBaseSystem> NewCameraSoftPtr, 
		float BlendTime = 1.f,
		float BlendExp = 0.0f,
		int32 Priority = 0
		);
	
	UFUNCTION(BlueprintCallable, Category = "Camera System")
	void ReturnToPlayerCamera(float BlendTime = 1.0f);
	
protected:
	UPROPERTY(Transient)
	TObjectPtr<ACameraBaseSystem> CurrentActiveCamera;
	
	int32 CurrentPriority = -1;
	
private:
	APlayerController* GetLocalPlayerController() const;
	
};
