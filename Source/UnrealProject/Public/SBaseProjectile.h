#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SBaseProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UParticleSystemComponent;
class UAudioComponent;
class USoundCue;
class UCameraShakeBase;

/*
 * The base class for projectiles in this project's game.
 */

UCLASS(ABSTRACT) // ABSTRACT marks as incomplete, and prevents certain dropdowns showing this.
class UNREALPROJECT_API ASBaseProjectile : public AActor
{
	GENERATED_BODY()

#pragma region Methods
public:	
	// Sets default values for this actor's properties
	ASBaseProjectile();

protected:
	void Explode_Implementation();
#pragma endregion Methods

#pragma region Properties
protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Components")
	USphereComponent* SphereComponent;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Components")
	UProjectileMovementComponent* MovementComponent;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Components")
	UParticleSystemComponent* EffectComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UAudioComponent* AudioComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	UParticleSystem* ImpactVFX;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	USoundCue* ImpactSound;

	UPROPERTY(EditDefaultsOnly, Category = "Effects|Shake")
	TSubclassOf<UCameraShakeBase> ImpactShake;

	UPROPERTY(EditDefaultsOnly, Category = "Effects|Shake")
	float ImpactShakeInnerRadius = 250.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Effects|Shake")
	float ImpactShakeOuterRadius = 500.0f;
#pragma endregion Properties
};
