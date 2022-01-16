#pragma once

#include "CoreMinimal.h"
#include "SBaseProjectile.h"
#include "SMagicProjectile.generated.h"

/*
 * The 'default' projectile in the project's game that does some damage on hit.
 */

UCLASS()
class UNREALPROJECT_API ASMagicProjectile : public ASBaseProjectile
{
	GENERATED_BODY()

#pragma region Methods
public:	
	// Sets default values for this actor's properties
	ASMagicProjectile();

protected:
	UFUNCTION()
	void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	virtual void PostInitializeComponents() override;
#pragma endregion Methods

#pragma region Properties
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	float DamageOnImpact = 20.0f;
#pragma region Properties
};
