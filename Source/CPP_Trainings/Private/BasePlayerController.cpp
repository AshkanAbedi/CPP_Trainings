// Fill out your copyright notice in the Description page of Project Settings.

#include "BasePlayerController.h"
#include "BaseGameMode.h"
#include "CPP_Trainings/BasePawn.h"
#include "Kismet/GameplayStatics.h"

ABasePlayerController::ABasePlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABasePlayerController::BeginPlay()
{
	Super::BeginPlay();
	GameMode = GetCurrentGameMode();
	SetViewTarget(GameMode->CameraActors[0]);
	Pawn = GetCurrentPawn();
}

void ABasePlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	CheckScreenEdges();
}

ABaseGameMode* ABasePlayerController::GetCurrentGameMode() const
{
	if (ABaseGameMode* BaseGameMode = Cast<ABaseGameMode>(UGameplayStatics::GetGameMode(GetWorld())))
	{
		return BaseGameMode;
	}
	return nullptr;
}

ABasePawn* ABasePlayerController::GetCurrentPawn() const
{
	if (ABasePawn* BasePawn = Cast<ABasePawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)))
	{
		return BasePawn;
	}
	return nullptr;
}

void ABasePlayerController::CheckScreenEdges()
{
	const FVector PawnCurrentLocation = Pawn->GetActorLocation();
	FVector2d ScreenLocation;
	bool bIsOnScreen = this->ProjectWorldLocationToScreen(PawnCurrentLocation, ScreenLocation);
	FVector2D ViewportSize;
	GEngine->GameViewport->GetViewportSize(ViewportSize);

	if (!bIsOnScreen || ScreenLocation.X < 0 || ScreenLocation.X > ViewportSize.X || 
		ScreenLocation.Y < 0 || ScreenLocation.Y > ViewportSize.Y)
	{
		SetViewTargetWithBlend(GameMode->CameraActors[1], 1.f);
	}
}
