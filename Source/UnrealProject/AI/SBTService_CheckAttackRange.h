#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "SBTService_CheckAttackRange.generated.h"

/**
 *	Behaviour tree service node that checks a target is within attack range
 *	and within line of sight.
 */

UCLASS()
class UNREALPROJECT_API USBTService_CheckAttackRange : public UBTService
{

	GENERATED_BODY()

#pragma region Methods
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
#pragma endregion Methods

#pragma region Properties
protected:
	UPROPERTY(EditAnywhere, Category = "AI")
	FBlackboardKeySelector AttackRangeKey;

	UPROPERTY(EditAnywhere, Category = "AI")
	float AttackRange = 2000.0f;
#pragma endregion Properties	
};
