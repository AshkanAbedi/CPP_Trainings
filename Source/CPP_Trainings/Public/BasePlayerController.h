// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BasePlayerController.generated.h"

class ABaseGameMode;
class ABasePawn;

UCLASS()
class CPP_TRAININGS_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ABasePlayerController();
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	ABaseGameMode* GetCurrentGameMode() const;
	ABasePawn* GetCurrentPawn() const;
	void CheckScreenEdges();
	
private:
	TObjectPtr<ABaseGameMode> GameMode;
	TObjectPtr<ABasePawn> Pawn;
	
};
