// Fill out your copyright notice in the Description page of Project Settings.


#include "SHealthPotion.h"
#include "SAttributeComponent.h"

// Sets default values
ASHealthPotion::ASHealthPotion()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	RootComponent = BaseMesh;

}

// Called when the game starts or when spawned
void ASHealthPotion::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASHealthPotion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ASHealthPotion::Interact_Implementation(APawn* InstigatorPawn)
{
	if (!GetWorldTimerManager().IsTimerActive(TimerHandle_HealthInactive))
	{
		USAttributeComponent* AttributeComponent = Cast<USAttributeComponent>(InstigatorPawn->GetComponentByClass(USAttributeComponent::StaticClass()));

		if (AttributeComponent && !AttributeComponent->IsMaxHealth())
		{
			AttributeComponent->ApplyHealthChange(HealthIncrease);
			BaseMesh->SetVisibility(false);
			GetWorldTimerManager().SetTimer(TimerHandle_HealthInactive, this, &ASHealthPotion::OnTimer_HealthInactiveElapsed, RespawnTimer);
		}
	}
}

void ASHealthPotion::OnTimer_HealthInactiveElapsed()
{
	BaseMesh->SetVisibility(true);
}
