// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SBaseProjectile.h"
#include "SMagicTeleportProjectile.generated.h"

UCLASS()
class UNREALPROJECT_API ASMagicTeleportProjectile : public ASBaseProjectile
{
	GENERATED_BODY()

public:

	ASMagicTeleportProjectile();

protected:

	virtual void BeginPlay() override;

	void Detonate();

	void Teleport();

	virtual void PostInitializeComponents() override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

protected:
	UPROPERTY(EditAnywhere, Category = "Teleportation")
	float TeleportationTime = 0.4f;

	UPROPERTY(EditAnywhere, Category = "Teleportation")
	UParticleSystem* ExplosionEmitter;

	FTimerHandle TimerHandle_Teleportation;
};
