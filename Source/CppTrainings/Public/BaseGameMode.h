// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BaseGameMode.generated.h"

UCLASS()
class CPPTRAININGS_API ABaseGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ABaseGameMode();
	virtual void BeginPlay() override;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TArray<AActor*> CameraActors;
	
};
