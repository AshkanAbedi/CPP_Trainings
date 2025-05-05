// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

class ABasePlayerController;
class UInputMappingContext;
class UInputAction;
struct FInputActionInstance;
class UBaseAbilitySystemComponent;
class UBaseAttributeSet;

UENUM(BlueprintType)
enum class EPlayerStates : uint8
{
	Normal,
	Walking,
	Turning
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MoveRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float TurnRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float Velocity;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	EPlayerStates PlayerStates;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	bool bIsWalking;

	void MoveForward(const FInputActionInstance& Value);
	void TurnRight(const FInputActionInstance& Value);
	void TurnLeft(const FInputActionInstance& Value);
	void StopMoving();
	ABasePlayerController* GetPlayerController() const;
	static void StatFPS();

protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities")
	TObjectPtr<UBaseAbilitySystemComponent> BaseAbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities")
	TObjectPtr<UBaseAttributeSet> BaseAttributeSet;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
