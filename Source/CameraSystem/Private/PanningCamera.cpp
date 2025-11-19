// Fill out your copyright notice in the Description page of Project Settings.
// ReSharper disable CppTooWideScope
// ReSharper disable CppLocalVariableMayBeConst
#include "PanningCamera.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"

APanningCamera::APanningCamera()
{
	PrimaryActorTick.bCanEverTick = true;
	bTrackPitch = true;
	bTrackYaw = true;
	RotationInterpSpeed = 5.0f;
}

void APanningCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	FRotator CurrentRotation = GetActorRotation();
	FRotator TargetRotation = GetLookAtRotation();
	
	if (!bTrackYaw) 
		TargetRotation.Yaw = CurrentRotation.Yaw;
	if (!bTrackPitch) 
		TargetRotation.Pitch = CurrentRotation.Pitch;
		
	TargetRotation.Roll = CurrentRotation.Roll;
	
	FRotator NewRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, DeltaTime, RotationInterpSpeed);
	SetActorRotation(NewRotation);
}

FRotator APanningCamera::GetLookAtRotation() const
{
	const APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (PlayerPawn)
	{
		FVector CameraLocation = GetActorLocation();
		FVector PlayerLocation = PlayerPawn->GetActorLocation();
		
		PlayerLocation.Z += 50.0f;
		
		return (PlayerLocation - CameraLocation).Rotation();
	}
	
	return GetActorRotation();
}

