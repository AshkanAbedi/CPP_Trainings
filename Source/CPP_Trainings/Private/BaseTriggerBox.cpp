// Fill out your copyright notice in the Description page of Project Settings.
// ReSharper disable CppMemberFunctionMayBeConst

#include "BaseTriggerBox.h"
#include "BaseMacros.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "BaseCharacter.h"
#include "BasePlayerController.h"
#include "BaseCamera.h"


// Sets default values
ABaseTriggerBox::ABaseTriggerBox()
{
	PrimaryActorTick.bCanEverTick = false;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetCollisionProfileName(TEXT("Trigger"));
	BoxComponent->SetGenerateOverlapEvents(true);
	RootComponent = BoxComponent;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(BoxComponent);
	StaticMeshComponent->SetCollisionProfileName(TEXT("NoCollision"));
	StaticMeshComponent->SetGenerateOverlapEvents(false);
	StaticMeshComponent->SetVisibility(true);
	StaticMeshComponent->SetHiddenInGame(true);

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ABaseTriggerBox::OnOverlapBegin);
	
}

// Called when the game starts or when spawned
void ABaseTriggerBox::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseTriggerBox::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                     UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (const ABaseCharacter* Player = Cast<ABaseCharacter>(OtherActor))
	{
		if (ABasePlayerController* PlayerController = Player->GetPlayerController(); RelatedCamera && PlayerController)
		{
			PlayerController->SwitchCamera(RelatedCamera);
			PRINT(1, "TriggerBox Number: %s" , Green, *GetName());
			PRINT(2, "Camera Name: %s" , Green, *RelatedCamera->GetName());
		}
	}
}


