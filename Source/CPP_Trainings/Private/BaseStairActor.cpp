// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseStairActor.h"

ABaseStairActor::ABaseStairActor()
{
	PrimaryActorTick.bCanEverTick = false;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));

	StaticMeshComponent->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	StaticMeshComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	StaticMeshComponent->SetGenerateOverlapEvents(true);
	StaticMeshComponent->CanCharacterStepUpOn = ECB_Yes;
	
}

void ABaseStairActor::BeginPlay()
{
	Super::BeginPlay();
}

