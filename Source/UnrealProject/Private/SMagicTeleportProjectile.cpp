// Fill out your copyright notice in the Description page of Project Settings.


#include "SMagicTeleportProjectile.h"
#include "SBaseProjectile.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

ASMagicTeleportProjectile::ASMagicTeleportProjectile() : ASBaseProjectile() {}

void ASMagicTeleportProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	SphereComponent->OnComponentHit.AddDynamic(this, &ASMagicTeleportProjectile::OnHit);
}


void ASMagicTeleportProjectile::BeginPlay()
{
	// Run parent constructor
	Super::BeginPlay();

	SphereComponent->IgnoreActorWhenMoving(GetInstigator(), true);

	// Start timer for detonation
	GetWorldTimerManager().SetTimer(TimerHandle_Teleportation, this, &ASMagicTeleportProjectile::Teleport, TeleportationTime);
}

void ASMagicTeleportProjectile::Teleport()
{
	// Get location and rotation to spawn instigator to
	FVector PlayerLocation = GetActorLocation();
	FRotator PlayerRotation = GetInstigator()->GetActorRotation();

	// Check instigator is not a nullptr
	AActor* OriginalInstigator = GetInstigator();
	if (OriginalInstigator)
		OriginalInstigator->TeleportTo(PlayerLocation, PlayerRotation);

	Explode_Implementation();
}

void ASMagicTeleportProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	GetWorldTimerManager().ClearTimer(TimerHandle_Teleportation);
	Teleport();
}
