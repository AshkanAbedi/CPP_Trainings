// Fill out your copyright notice in the Description page of Project Settings.
#include "BaseCameraRail.h"
#include "BaseMacros.h"
#include "BaseCamera.h"
#include "Camera/CameraComponent.h"

ABaseCameraRail::ABaseCameraRail(const FObjectInitializer& ObjectInitializer): ACameraRig_Rail(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	CameraActorComponent = CreateDefaultSubobject<UChildActorComponent>(TEXT("Camera Actor"));
	CameraActorComponent->SetupAttachment(this->RailCameraMount);
	CameraActorComponent->SetChildActorClass(ABaseCamera::StaticClass());
}


void ABaseCameraRail::BeginPlay()
{
	Super::BeginPlay();

	if (ABaseCamera* RailCamera = Cast<ABaseCamera>(CameraActorComponent->GetChildActor()))
	{
		RailCamera->bFollowCharacter = true;
		RailCamera->GetCameraComponent()->SetFieldOfView((65.0f));
		RailCamera->GetCameraComponent()->SetAspectRatio(16.0f / 9.0f);
	}
}

void ABaseCameraRail::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	CurrentPositionOnRail = FMath::Clamp(CurrentPositionOnRail + DeltaSeconds * MoveSpeed, 0.0f, 1.0f);

	PRINT(3, "Current Position on Rail: %f", Green, CurrentPositionOnRail);
}

