// Fill out your copyright notice in the Description page of Project Settings.


#include "SBTTaskNode_Heal.h"
#include "SAttributeComponent.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type USBTTaskNode_Heal::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (ensure(AIController))
	{
		APawn* AIPawn = Cast<APawn>(AIController->GetPawn());
		if (AIPawn == nullptr)
		{
			return EBTNodeResult::Failed;
		}

		UBlackboardComponent* BlackboardComponent = AIController->GetBlackboardComponent();
		if (BlackboardComponent == nullptr)
		{
			return EBTNodeResult::Failed;
		}

		USAttributeComponent* AttributeComponent = Cast<USAttributeComponent>(AIPawn->GetComponentByClass(USAttributeComponent::StaticClass()));
		if (ensure(AttributeComponent))
		{
			AttributeComponent->ApplyHealthChange(AmountToHeal);
			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}
