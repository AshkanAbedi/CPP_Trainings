// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseStairActor.generated.h"

class UBoxComponent;
class UShapeComponent;
class UStaticMeshComponent;
class ABaseCharacter;

UCLASS()
class CPPTRAININGS_API ABaseStairActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ABaseStairActor();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
	TObjectPtr<UBoxComponent> TriggerBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnTriggerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
