#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STargetDummy.generated.h"

class USAttributeComponent;

/*
 * Target dummy actor to check implementation of material changes on damage taken.
 */

UCLASS()
class UNREALPROJECT_API ASTargetDummy : public AActor
{
	GENERATED_BODY()

#pragma region Methods
public:	
	ASTargetDummy();
#pragma endregion Methods

#pragma region Properties
protected:
	UPROPERTY(VisibleAnywhere)
	USAttributeComponent* AttributeComponent;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComponent;

	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComponent, float NewHealth, float Delta);
#pragma endregion Properties
};
