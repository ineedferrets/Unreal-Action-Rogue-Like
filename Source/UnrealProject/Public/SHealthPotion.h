#pragma once

#include "CoreMinimal.h"
#include "SPowerUPActor.h"
#include "SHealthPotion.generated.h"

class UStaticMeshComponent;

/*
 * Base class for a health potion that inherits from ASPowerUpActor.
 */

UCLASS()
class UNREALPROJECT_API ASHealthPotion : public ASPowerUpActor
{
	GENERATED_BODY()

#pragma region Methods
	void Interact_Implementation(APawn* InstigatorPawn) override;
	
public:	
	// Sets default values for this actor's properties
	ASHealthPotion();
#pragma endregion Methods

#pragma region Properties
protected:
	UPROPERTY(EditAnywhere)
	float HealthIncrease = 20.0f;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;
#pragma endregion Properties
};
