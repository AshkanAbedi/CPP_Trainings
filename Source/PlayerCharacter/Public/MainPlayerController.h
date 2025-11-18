// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogBasePlayerController, Log, All);

class UInputMappingContext;

UCLASS()
class PLAYERCHARACTER_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	
protected:
	UPROPERTY(EditAnywhere, Category = "Input|Input Mappings")
	TArray<UInputMappingContext*> DefaultMappingContext;
	
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override; 
	
private:
};
