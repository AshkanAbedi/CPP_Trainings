// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseAnimInstance.h"
#include "BaseCharacter.h"
#include "BaseMacros.h"

void UBaseAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Character = Cast<ABaseCharacter>(TryGetPawnOwner());

	if (Character)
	{
		// Initialize any variables or perform setup here
		PRINT(1, "BaseAnimInstance Initialized", Green);
	}
	else
	{
		PRINT(2, "BaseAnimInstance Failed to Initialize", Red);
	}
}

void UBaseAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
}
