// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BasePlayerController.generated.h"

class ABaseCamera;
class ABaseGameMode;
class ABaseCharacter;

UCLASS()
class CPP_TRAININGS_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ABasePlayerController();
	void SwitchCamera(ABaseCamera* NewCamera);
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	ABaseGameMode* GetCurrentGameMode() const;
	ABaseCharacter* GetCurrentCharacter() const;
	void CheckScreenEdges();
	
private:
	TObjectPtr<ABaseGameMode> GameMode;
	TObjectPtr<ABaseCharacter> Character;
	
};
