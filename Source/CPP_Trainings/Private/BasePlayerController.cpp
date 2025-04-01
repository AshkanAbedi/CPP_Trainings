// Fill out your copyright notice in the Description page of Project Settings.

#include "BasePlayerController.h"
#include "BaseGameMode.h"
#include "BaseCharacter.h"
#include "BaseCamera.h"
#include "Components/BoxComponent.h"
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
	Character = GetCurrentCharacter();
}

void ABasePlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

ABaseGameMode* ABasePlayerController::GetCurrentGameMode() const
{
	if (ABaseGameMode* BaseGameMode = Cast<ABaseGameMode>(UGameplayStatics::GetGameMode(GetWorld())))
	{
		return BaseGameMode;
	}
	return nullptr;
}

ABaseCharacter* ABasePlayerController::GetCurrentCharacter() const
{
	if (ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
	{
		return BaseCharacter;
	}
	return nullptr;
}

void ABasePlayerController::SwitchCamera(ABaseCamera* NewCamera)
{
	if (NewCamera && GetViewTarget() != NewCamera)
	{
		if (const ABaseCamera* PreviousCamera = Cast<ABaseCamera>(GetViewTarget()))
		{
			PreviousCamera->BoxComponent01->SetGenerateOverlapEvents(true);
			PreviousCamera->BoxComponent02->SetGenerateOverlapEvents(true);
		}
		
		SetViewTarget(NewCamera);
		NewCamera->BoxComponent01->SetGenerateOverlapEvents(false);
		NewCamera->BoxComponent02->SetGenerateOverlapEvents(false);
	}
}


void ABasePlayerController::CheckScreenEdges()
{
	const FVector CharacterCurrentLocation = Character->GetActorLocation();
	FVector2d ScreenLocation;
	const bool bIsOnScreen = this->ProjectWorldLocationToScreen(CharacterCurrentLocation, ScreenLocation);
	FVector2D ViewportSize;
	GEngine->GameViewport->GetViewportSize(ViewportSize);

	if (!bIsOnScreen || ScreenLocation.X < 0 || ScreenLocation.X > ViewportSize.X || 
		ScreenLocation.Y < 0 || ScreenLocation.Y > ViewportSize.Y)
	{
		SetViewTarget(GameMode->CameraActors[1]);
	}
}
