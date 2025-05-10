// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseStairActor.generated.h"

class UStaticMeshComponent;
class ABaseCharacter;

UCLASS()
class CPP_TRAININGS_API ABaseStairActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ABaseStairActor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

protected:
	virtual void BeginPlay() override;

};
