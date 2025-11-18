// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseTriggerBox.generated.h"

class UStaticMeshComponent;
class UBoxComponent;
class ABaseCamera;
class ABasePlayerController;
class ABaseCharacter;

UCLASS()
class CPPTRAININGS_API ABaseTriggerBox : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ABaseTriggerBox();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Components)
	TObjectPtr<UBoxComponent> BoxComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera)
	TObjectPtr<ABaseCamera> RelatedCamera;

	bool bIsActive;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
