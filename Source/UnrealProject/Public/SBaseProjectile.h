// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SBaseProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UParticleSystemComponent;

UCLASS()
class UNREALPROJECT_API ASBaseProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASBaseProjectile();

protected:

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	USphereComponent* SphereComponent;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UProjectileMovementComponent* MovementComponent;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UParticleSystemComponent* EffectComponent;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float ParticleVelocity = 1000.0f;

};
