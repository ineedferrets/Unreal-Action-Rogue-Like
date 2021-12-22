// Fill out your copyright notice in the Description page of Project Settings.



#include "SBTService_CheckAttackRange.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

void USBTService_CheckAttackRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	// Check distance between AI and Pawn
	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();

	if (ensure(BlackboardComponent))
	{
		AActor* TargetActor = Cast<AActor>(BlackboardComponent->GetValueAsObject("TargetActor"));
		if (TargetActor)
		{
			AAIController* AIController = OwnerComp.GetAIOwner();
			if (ensure(AIController))
			{
				APawn* AIPawn = AIController->GetPawn();
				if (ensure(AIPawn))
				{
					float Distance = FVector::Distance(TargetActor->GetActorLocation(), AIPawn->GetActorLocation());

					bool bWithinRange = Distance < AttackRange;

					bool bHasLOS = false;
					if (bWithinRange)
					{
						bHasLOS = AIController->LineOfSightTo(TargetActor);
					}

					BlackboardComponent->SetValueAsBool(AttackRangeKey.SelectedKeyName, (bWithinRange && bHasLOS));
				}
			}
		}
	}

	// Line of sight check
}
