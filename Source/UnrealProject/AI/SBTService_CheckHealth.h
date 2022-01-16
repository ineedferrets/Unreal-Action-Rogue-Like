#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "SBTService_CheckHealth.generated.h"

/**
 * Behaviour tree service node that checks the AIs health and adjusts two boolean
 * blackboard variables to indicate whether it is at max and low health.
 */

UCLASS()
class UNREALPROJECT_API USBTService_CheckHealth : public UBTService
{
	GENERATED_BODY()

#pragma region Methods
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
#pragma endregion Methods

#pragma region Properties
protected:
	UPROPERTY(EditAnywhere, Category = "AI")
	FBlackboardKeySelector IsLowHealth;

	UPROPERTY(EditAnywhere, Category = "AI")
	float LowHealthPercentage = 0.3;

	UPROPERTY(EditAnywhere, Category = "AI")
	FBlackboardKeySelector IsMaxHealth;
#pragma endregion Properties
};
