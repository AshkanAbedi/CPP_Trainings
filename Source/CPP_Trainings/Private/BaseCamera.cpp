// Fill out your copyright notice in the Description page of Project Settings.

// ReSharper disable CppMemberFunctionMayBeStatic
// ReSharper disable CppParameterMayBeConstPtrOrRef
#include "BaseCamera.h"
#include "BaseMacros.h"
#include "BasePlayerController.h"
#include "Components/BoxComponent.h"
#include "CPP_Trainings/BasePawn.h"

ABaseCamera::ABaseCamera()
{
	BoxComponent01 = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Box 1"));
	BoxComponent01->SetupAttachment(RootComponent);
	BoxComponent01->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BoxComponent01->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	BoxComponent01->OnComponentBeginOverlap.AddDynamic(this, &ABaseCamera::OnEnterTriggerBox);

	BoxComponent02 = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Box 2"));
	BoxComponent02->SetupAttachment(RootComponent);
	BoxComponent02->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BoxComponent02->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	BoxComponent02->OnComponentBeginOverlap.AddDynamic(this, &ABaseCamera::OnEnterTriggerBox);
}

void ABaseCamera::OnEnterTriggerBox(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	PRINT(-1, "Camera Triggered: %s", Purple, *this->GetName());
	
	if (const ABasePawn* Pawn = Cast<ABasePawn>(OtherActor))
	{
		if (ABasePlayerController* PlayerController = Cast<ABasePlayerController>(Pawn->GetController()))
		{
			PlayerController->SwitchCamera(this);
		}
	}
}
