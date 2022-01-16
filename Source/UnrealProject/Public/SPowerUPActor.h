#pragma once

#include "CoreMinimal.h"
#include "SGameplayInterface.h"
#include "GameFramework/Actor.h"
#include "SPowerUPActor.generated.h"

class USphereComponent;

/*
 * Base class for any power ups.
 */

UCLASS(Abstract)
class UNREALPROJECT_API ASPowerUpActor : public AActor, public ISGameplayInterface
{
	GENERATED_BODY()

#pragma region Methods
	void Interact_Implementation(APawn* InstigatorPawn) override;
	
public:	
	ASPowerUpActor();

protected:
	void ShowPowerUp();

	void HideAndCooldownPowerUp();

	void SetPowerUpState(bool bNewIsActive);
#pragma endregion Methods

#pragma region Properties
protected:
	UPROPERTY(VisibleAnywhere)
	USphereComponent* SphereComponent;

	UPROPERTY(EditAnywhere, Category = "Power Up")
	float RespawnTime = 10.0f;

	FTimerHandle TimerHandle_RespawnTimer;
#pragma endregion Properties
};
