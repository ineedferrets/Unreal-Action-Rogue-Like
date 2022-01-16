#pragma once

#include "CoreMinimal.h"
#include "SBaseProjectile.h"
#include "SMagicTeleportProjectile.generated.h"

/*
 * A projectile that teleports the caster after an elapsed time to point of projectile.
 */

UCLASS()
class UNREALPROJECT_API ASMagicTeleportProjectile : public ASBaseProjectile
{
	GENERATED_BODY()

#pragma region Methods
public:
	ASMagicTeleportProjectile();

protected:
	virtual void BeginPlay() override;

	void Teleport();

	virtual void PostInitializeComponents() override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
#pragma endregion Methods

#pragma region Properties
protected:
	UPROPERTY(EditAnywhere, Category = "Teleportation")
	float TeleportationTime = 0.4f;

	FTimerHandle TimerHandle_Teleportation;
#pragma endregion Properties
};
