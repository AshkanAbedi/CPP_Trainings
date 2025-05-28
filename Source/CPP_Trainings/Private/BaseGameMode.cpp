// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseGameMode.h"
#include "BaseMacros.h"
#include "BaseCamera.h"
#include "Kismet/GameplayStatics.h"

ABaseGameMode::ABaseGameMode()
{
	
}

void ABaseGameMode::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::GetAllActorsOfClass(this, ABaseCamera::StaticClass(), CameraActors);

	for (const AActor* CameraActor : CameraActors)
	{
		PRINT(-1, "Camera Actor Found: %s", Purple, *CameraActor->GetName());
	}
}
