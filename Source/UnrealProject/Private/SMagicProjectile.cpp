#include "SMagicProjectile.h"
#include "Components/SphereComponent.h"
#include "DrawDebugHelpers.h"
#include "SGameplayFunctionLibrary.h"

#pragma region Initialisation
// Sets default values
ASMagicProjectile::ASMagicProjectile() : ASBaseProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ASMagicProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ASMagicProjectile::OnActorOverlap);
	SphereComponent->OnComponentHit.AddDynamic(this, &ASMagicProjectile::OnHit);
}
#pragma endregion Initialisation

#pragma region Collisions
void ASMagicProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != GetInstigator())
	{
		if (USGameplayFunctionLibrary::ApplyDirectionalDamage(GetInstigator(), OtherActor, DamageOnImpact, SweepResult))
		{
			Explode_Implementation();
		}
	}
}

void ASMagicProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	DrawDebugSphere(GetWorld(), Hit.ImpactPoint, 10.0f, 12, FColor::Red, false, 2.0f);

	Explode_Implementation();
}
#pragma endregion Collisions