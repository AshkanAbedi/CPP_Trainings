// Fill out your copyright notice in the Description page of Project Settings.
#include "CameraDirectorSubsystem.h"
#include "CameraBaseSystem.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"

void UCameraDirectorSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	CurrentActiveCamera = nullptr;
	CurrentPriority = -1;
	
	UE_LOG(LogTemp, Warning, TEXT("CameraDirectorSubsystem Initialized"));
}

void UCameraDirectorSubsystem::Deinitialize()
{
	CurrentActiveCamera = nullptr;
	Super::Deinitialize();
	
}

void UCameraDirectorSubsystem::RequestCameraChange(TSoftObjectPtr<ACameraBaseSystem> NewCameraSoftPtr, const float BlendTime,
	const float BlendExp, int32 Priority)
{
	if (CurrentActiveCamera && CurrentPriority > Priority) return;
	
	ACameraBaseSystem* NewCamera = NewCameraSoftPtr.LoadSynchronous();
	
	if (!NewCamera)
	{
		UE_LOG(LogTemp, Warning, TEXT("RequestCameraChange: NewCamera is null"));
		return;
	}
	
	if (CurrentActiveCamera == NewCamera)
	{
		CurrentPriority = Priority;
		return;
	}
	
	if (CurrentActiveCamera)
	{
		CurrentActiveCamera->OnBecomeInactive();
	}
	
	CurrentActiveCamera = NewCamera;
	CurrentPriority = Priority;
	
	CurrentActiveCamera->OnBecomeActive();
	
	if (APlayerController* PC = GetLocalPlayerController())
	{
		AActor* NewCameraActor = Cast<AActor>(NewCamera);
		PC->SetViewTargetWithBlend(NewCameraActor, BlendTime, EViewTargetBlendFunction::VTBlend_Cubic, BlendExp);
	}
}

void UCameraDirectorSubsystem::ReturnToPlayerCamera(float BlendTime)
{
	if (CurrentActiveCamera)
	{
		CurrentActiveCamera->OnBecomeInactive();
	}
	
	CurrentActiveCamera = nullptr;
	CurrentPriority = -1;
	
	if (APlayerController* PC = GetLocalPlayerController())
	{
		if (APawn* PlayerPawn = PC->GetPawn())
		{
			PC->SetViewTargetWithBlend(PlayerPawn, BlendTime, EViewTargetBlendFunction::VTBlend_Cubic);
		}
		else
		{
			PC->SetViewTarget(PC);
		}
	}
}

APlayerController* UCameraDirectorSubsystem::GetLocalPlayerController() const
{
	if (const UWorld* World = GetWorld())
	{
		return World->GetFirstPlayerController();
	}
	
	return nullptr;
}


