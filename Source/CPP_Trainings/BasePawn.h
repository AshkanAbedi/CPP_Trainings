// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

struct FInputActionInstance;
class USkeletalMeshComponent;
//class UCameraComponent;
class UArrowComponent;
class UInputComponent;
class UInputAction;
class UInputMappingContext;

UENUM(BlueprintType)
enum class EPlayerStates : uint8
{
	Normal,
	Walking,
	Turning
};

UCLASS()
class CPP_TRAININGS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USceneComponent> SceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<USkeletalMeshComponent> BaseSkeletalMesh;

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UCameraComponent> BaseCamera;*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UArrowComponent> ForwardArrow;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputAction> InputMoveForward;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputAction> InputTurnRight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputAction> InputTurnLeft;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float SpeedMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float TurnRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float Velocity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pawn|State")
	EPlayerStates PlayerStates;
	
	void MoveForward (const FInputActionInstance& Value);
	void Turn (const FInputActionInstance& Value);
	void StopMoving();
	static void CastRecognition();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

};
