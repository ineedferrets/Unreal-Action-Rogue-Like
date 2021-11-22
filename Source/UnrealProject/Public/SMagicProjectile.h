// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SBaseProjectile.h"
#include "SMagicProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UParticleSystemComponent;
class UAudioComponent;
class USoundBase;

UCLASS()
class UNREALPROJECT_API ASMagicProjectile : public ASBaseProjectile
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	ASMagicProjectile();

protected:
	UFUNCTION()
	void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);


	virtual void PostInitializeComponents() override;

	UPROPERTY(EditAnywhere, Category = "Magic Projectile")
	UParticleSystem* ImpactEmitter;

	UPROPERTY(EditAnywhere, Category = "Magic Projectile")
	USoundBase* ImpactSound;

	UPROPERTY(VisibleAnywhere, Category = "Magic Projectile")
	UAudioComponent* AudioComponent;

private:

	void PlayImpactEffects();
};
