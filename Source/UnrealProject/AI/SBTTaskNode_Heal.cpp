#include "SBTTaskNode_Heal.h"
#include "SAttributeComponent.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type USBTTaskNode_Heal::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (ensure(AIController))
	{
		// Check if Controller is controlling a pawn.
		APawn* AIPawn = Cast<APawn>(AIController->GetPawn());
		if (AIPawn == nullptr)
		{
			return EBTNodeResult::Failed;
		}

		// Check if a blackboard component is present in the controller.
		UBlackboardComponent* BlackboardComponent = AIController->GetBlackboardComponent();
		if (BlackboardComponent == nullptr)
		{
			return EBTNodeResult::Failed;
		}

		// Check if pawn has an attribute component.
		USAttributeComponent* AttributeComponent = USAttributeComponent::GetAttributes(AIPawn);
		if (ensure(AttributeComponent))
		{
			// Heal pawn.
			AttributeComponent->ApplyHealthChange(AIPawn, AmountToHeal);
			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}
