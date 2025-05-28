// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

class ABasePlayerController;
class UBaseAbilitySystemComponent;
class UBaseAttributeSet;
class UInputMappingContext;
class UInputAction;
struct FInputActionInstance;

UENUM(BlueprintType)
enum class EPlayerStates : uint8
{
	Normal,
	Walking,
	OnStairs
};

UCLASS(config=Game)
class CPP_TRAININGS_API ABaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	
	ABaseCharacter();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputAction> InputMoveForward;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputAction> InputTurnRight;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputAction> InputTurnLeft;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float DefaultWalkSpeed;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float OnStairsSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float TurnRate;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float Velocity;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	EPlayerStates PlayerStates;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	bool bIsWalking;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	bool bIsOnStair;

	void MoveForward(const FInputActionInstance& Value);
	void TurnRight(const FInputActionInstance& Value);
	void TurnLeft(const FInputActionInstance& Value);
	void StopMoving();
	void SetIsOnStairs(bool bNewIsOnStairs);
	TObjectPtr<ABasePlayerController> GetPlayerController() const;

protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities")
	TObjectPtr<UBaseAbilitySystemComponent> BaseAbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities")
	TObjectPtr<UBaseAttributeSet> BaseAttributeSet;
	
	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;
	FTimerHandle TraceTimerHandle;
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	void Tracing();
	void UpdatePlayerState();

	
#if UE_BUILD_DEBUG
	static void StatFPS();
#endif
	
};
