#include "SInteractionComponent.h"
#include "CollisionQueryParams.h"
#include "CollisionShape.h"
#include "DrawDebugHelpers.h"
#include "SGameplayInterface.h"

#pragma region Console Variables
static TAutoConsoleVariable<bool> CVarDebugDrawInteraction(TEXT("jh.InteractionDebugDraw"), false, TEXT("Enable Debug Lines for Interact Component"), ECVF_Cheat);
#pragma endregion Console Variables

#pragma region Initialisation
USInteractionComponent::USInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}
#pragma endregion Initialisation

void USInteractionComponent::PrimaryInteract()
{
	bool bDebugDraw = CVarDebugDrawInteraction.GetValueOnGameThread();

	AActor* Owner = GetOwner();

	// Get start and end point of sweep.
	FVector EyeLocation;
	FRotator EyeRotation;
	Owner->GetActorEyesViewPoint(EyeLocation, EyeRotation);
	FVector End = EyeLocation + (EyeRotation.Vector() * 1000);

	TArray<FHitResult> Hits;

	// Set sweep parameters.
	float Radius = 30.0f;
	FCollisionShape Shape;
	Shape.SetSphere(Radius);
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	// Sweep!
	bool bBlockingHit = GetWorld()->SweepMultiByObjectType(Hits, EyeLocation, End, FQuat::Identity, ObjectQueryParams, Shape);

	// Debug draw based on successful block.
	FColor SphereColor = bBlockingHit ? FColor::Green : FColor::Red;

	for (FHitResult Hit : Hits)
	{
		if (bDebugDraw)
			DrawDebugSphere(GetWorld(), Hit.ImpactPoint, Radius, 32, SphereColor, false, 2.0f);

		AActor* HitActor = Hit.GetActor();
		if (HitActor)
		{
			if (HitActor->Implements<USGameplayInterface>())
			{
				APawn* OwnerPawn = Cast<APawn>(Owner);

				ISGameplayInterface::Execute_Interact(HitActor, OwnerPawn);
				break;
			}
		}
	}

	if (bDebugDraw)
		DrawDebugLine(GetWorld(), EyeLocation, End, SphereColor, false, 2.0f, 0, 2.0f);
}
