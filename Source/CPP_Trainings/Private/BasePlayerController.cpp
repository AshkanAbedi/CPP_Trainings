// Fill out your copyright notice in the Description page of Project Settings.

#include "BasePlayerController.h"

ABasePlayerController::ABasePlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABasePlayerController::BeginPlay()
{
	Super::BeginPlay();
	
}
