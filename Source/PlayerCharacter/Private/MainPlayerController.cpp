// Fill out your copyright notice in the Description page of Project Settings.
#include "MainPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

void AMainPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogBasePlayerController, Warning, TEXT("BasePlayerController Initiated"));
}

void AMainPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		for (UInputMappingContext* CurrentContext : DefaultMappingContext)
		{
			Subsystem->AddMappingContext(CurrentContext, 0);
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Added Mapping Context: %s"), *CurrentContext->GetName()));
		}
	}
	
}


