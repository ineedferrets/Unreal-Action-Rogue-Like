// Fill out your copyright notice in the Description page of Project Settings.


#include "SPowerUPActor.h"

#include "Components/SphereComponent.h"

// Sets default values
ASPowerUPActor::ASPowerUPActor()
{
	SphereComponent = CreateAbstractDefaultSubobject<USphereComponent>("SphereComponent");
	SphereComponent->SetCollisionProfileName("Powerup");
	RootComponent = SphereComponent;
}

void ASPowerUPActor::Interact_Implementation(APawn* InstigatorPawn)
{
	// Logic in derived classes!
}

void ASPowerUPActor::ShowPowerup()
{
	SetPowerupState(true);
}

void ASPowerUPActor::HideAndCooldownPowerup()
{
	SetPowerupState(false);

	GetWorldTimerManager().SetTimer(TimerHandle_RespawnTimer, this, &ASPowerUPActor::ShowPowerup, RespawnTime);
}

void ASPowerUPActor::SetPowerupState(bool bNewIsActive)
{
	SetActorEnableCollision(bNewIsActive);

	RootComponent->SetVisibility(bNewIsActive, true);
}
