// Fill out your copyright notice in the Description page of Project Settings.


#include "SInteractionComponent.h"

#include "DrawDebugHelpers.h"
#include "SGameplayInterface.h"

// Sets default values for this component's properties
USInteractionComponent::USInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USInteractionComponent::PrimaryInteract()
{
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	AActor* Owner = GetOwner();

	FVector EyeLocation;
	FRotator EyeRotation;
	Owner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

	FVector End = EyeLocation + (EyeRotation.Vector() * 1000);

	//FHitResult Hit;
	//bool bBlockingHit = GetWorld()->LineTraceSingleByObjectType(Hit, EyeLocation, End, ObjectQueryParams);

	TArray<FHitResult> Hits;

	float Radius = 30.0f;

	FCollisionShape Shape;
	Shape.SetSphere(Radius);

	bool bBlockingHit = GetWorld()->SweepMultiByObjectType(Hits, EyeLocation, End, FQuat::Identity, ObjectQueryParams, Shape);

	FColor SphereColor = bBlockingHit ? FColor::Green : FColor::Red;

	for (FHitResult Hit : Hits)
	{
		AActor* HitActor = Hit.GetActor();
		if (HitActor)
		{
			if (HitActor->Implements<USGameplayInterface>())
			{
				APawn* OwnerPawn = Cast<APawn>(Owner);

				ISGameplayInterface::Execute_Interact(HitActor, OwnerPawn);
			}
		}

		DrawDebugSphere(GetWorld(), Hit.ImpactPoint, Radius, 32, SphereColor, false, 2.0f);
	}

	DrawDebugLine(GetWorld(), EyeLocation, End, SphereColor, false, 2.0f, 0, 2.0f);
}
