#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "SBTTaskNode_Heal.generated.h"

/**
 * Behaviour tree task to heal the controller pawn through its attribute component.
 */

UCLASS()
class UNREALPROJECT_API USBTTaskNode_Heal : public UBTTaskNode
{
	GENERATED_BODY()

#pragma region Methods
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
#pragma endregion Methods

#pragma region Properties
	UPROPERTY(EditAnywhere, Category = "AI")
	float AmountToHeal = 20.0f;
#pragma region Properties
};
