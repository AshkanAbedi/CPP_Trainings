// Fill out your copyright notice in the Description page of Project Settings.
// ReSharper disable CppTooWideScope
// ReSharper disable CppTooWideScopeInitStatement
#include "CameraTriggerVolume.h"
#include "CameraDirectorSubsystem.h"
#include "CameraBaseSystem.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"

ACameraTriggerVolume::ACameraTriggerVolume()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACameraTriggerVolume::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	const APawn* PlayerPawn = Cast<APawn>(OtherActor);
	if (!PlayerPawn || !PlayerPawn->IsPlayerControlled()) return;
	
	if (CameraToActivate.IsNull())
	{
		UE_LOG(LogTemp, Warning, TEXT("CameraTriggerVolume: CameraToActivate is null"));
		return;
	}

	const UWorld* World = GetWorld();
	if (!World) return;
	
	UCameraDirectorSubsystem* CameraDirector = World->GetSubsystem<UCameraDirectorSubsystem>();
	if (CameraDirector)
	{
		CameraDirector->RequestCameraChange(CameraToActivate, BlendTime, BlendExp, Priority);
	}
}

void ACameraTriggerVolume::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);

	const APawn* PlayerPawn = Cast<APawn>(OtherActor);
	if (!PlayerPawn || !PlayerPawn->IsPlayerControlled()) return;
	
	const UWorld* World = GetWorld();
	if (!World) return;
	
	UCameraDirectorSubsystem* CameraDirector = World->GetSubsystem<UCameraDirectorSubsystem>();
	if (CameraDirector)
	{
		CameraDirector->ReturnToPlayerCamera(BlendTime);
	}
	
}

