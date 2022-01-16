#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SExplosiveBarrel.generated.h"

class UStaticMeshComponent;
class URadialForceComponent;

/*
 * Actor class for an exploding barrel.
 */

UCLASS()
class UNREALPROJECT_API ASExplosiveBarrel : public AActor
{
	GENERATED_BODY()

#pragma region Methods
public:	
	ASExplosiveBarrel();

protected:
	virtual void PostInitializeComponents() override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
#pragma endregion Methods

#pragma region Properties
protected:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(VisibleAnywhere)
	URadialForceComponent* RadialForceComponent;
#pragma endregion Properties
};
