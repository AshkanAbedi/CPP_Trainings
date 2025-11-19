// Fill out your copyright notice in the Description page of Project Settings.
#include "CameraBaseSystem.h"

ACameraBaseSystem::ACameraBaseSystem()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;
}

void ACameraBaseSystem::BeginPlay()
{
	Super::BeginPlay();
	SetActorTickEnabled(false);
}

void ACameraBaseSystem::OnBecomeActive()
{
	SetActorTickEnabled(true);	
}

void ACameraBaseSystem::OnBecomeInactive()
{
	SetActorTickEnabled(false);
}

void ACameraBaseSystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

