// Fill out your copyright notice in the Description page of Project Settings.


#include "SMagicTeleportProjectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

ASMagicTeleportProjectile::ASMagicTeleportProjectile() : ASMagicProjectile()
{

}

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
	GetWorldTimerManager().SetTimer(TimerHandle_Teleportation, this, &ASMagicTeleportProjectile::Detonate, TeleportationTime / 2);
}

void ASMagicTeleportProjectile::Detonate()
{
	UE_LOG(LogTemp, Warning, TEXT("Detonation of Teleportation Projectile called."));

	FTransform EmitterTransform = GetActorTransform();
	// Play emitter
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionEmitter, EmitterTransform, true);

	// Stop movement
	MovementComponent->StopMovementImmediately();

	// Start timer for teleportation
	GetWorldTimerManager().SetTimer(TimerHandle_Teleportation, this, &ASMagicTeleportProjectile::Teleport, TeleportationTime / 2);
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

	// Destroy actor
	Destroy();
}

void ASMagicTeleportProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	GetWorldTimerManager().ClearTimer(TimerHandle_Teleportation);
	Detonate();
}
