// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseAnimInstance.h"
#include "CPP_Trainings/BasePawn.h"

void UBaseAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Pawn = Cast<ABasePawn>(TryGetPawnOwner());

	if (Pawn)
	{
		Pawn->CastRecognition();
	}
}

void UBaseAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
}
