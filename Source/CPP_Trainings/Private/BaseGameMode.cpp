// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseGameMode.h"

#include "BaseMacros.h"
#include "CPP_Trainings/BasePawn.h"
#include "BasePlayerController.h"
#include "Camera/CameraActor.h"
#include "Kismet/GameplayStatics.h"

ABaseGameMode::ABaseGameMode()
{
	DefaultPawnClass = ABasePawn::StaticClass();
	PlayerControllerClass = ABasePlayerController::StaticClass();
	
}

void ABaseGameMode::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> CameraActors;

	UGameplayStatics::GetAllActorsOfClass(this, ACameraActor::StaticClass(), CameraActors);

	for (const AActor* CameraActor : CameraActors)
	{
		PRINT(-1, "Camera Actor Found: %s", Purple, *CameraActor->GetName());
	}

	if (ABasePlayerController* PlayerController = Cast<ABasePlayerController>(UGameplayStatics::GetPlayerController(this, 0)))
	{
		PRINT(-1, "Player Controller Found: %s", Purple, *PlayerController->GetName());
		PlayerController->SetViewTarget(CameraActors[0]);
	}

	if (ABasePawn* Pawn = Cast<ABasePawn>(UGameplayStatics::GetPlayerPawn(this, 0)))
	{
		PRINT(-1, "Pawn Found: %s", Purple, *Pawn->GetName());
	}
	
}
