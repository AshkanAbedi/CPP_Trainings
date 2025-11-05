// Fill out your copyright notice in the Description page of Project Settings.
// ReSharper disable CppMemberFunctionMayBeStatic

#include "BaseStairActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "BaseCharacter.h"

ABaseStairActor::ABaseStairActor()
{
	PrimaryActorTick.bCanEverTick = false;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	RootComponent = StaticMeshComponent;
	StaticMeshComponent->SetCollisionProfileName(UCollisionProfile::BlockAllDynamic_ProfileName);

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(StaticMeshComponent);
	TriggerBox->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
	TriggerBox->SetGenerateOverlapEvents(true);
	TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	TriggerBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	TriggerBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	TriggerBox->SetBoxExtent(FVector(100, 100, 100));
	
}

void ABaseStairActor::BeginPlay()
{
	Super::BeginPlay();

	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ABaseStairActor::OnTriggerBeginOverlap);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &ABaseStairActor::OnTriggerEndOverlap);
}

void ABaseStairActor::OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ABaseCharacter* Character = Cast<ABaseCharacter>(OtherActor))
	{
		Character->SetIsOnStairs(true);
	}
}

void ABaseStairActor::OnTriggerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (ABaseCharacter* Character = Cast<ABaseCharacter>(OtherActor))
	{
		Character->SetIsOnStairs(false);
	}
}


