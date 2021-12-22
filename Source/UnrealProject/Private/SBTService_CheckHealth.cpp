// Fill out your copyright notice in the Description page of Project Settings.


#include "SBTService_CheckHealth.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "SAttributeComponent.h"

void USBTService_CheckHealth::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();

	if (ensure(BlackboardComponent))
	{
		AAIController* AIController = OwnerComp.GetAIOwner();
		if (ensure(AIController))
		{
			APawn* AIPawn = AIController->GetPawn();
			if (ensure(AIPawn))
			{
				USAttributeComponent* AttributeComponent = Cast<USAttributeComponent>(AIPawn->GetComponentByClass(USAttributeComponent::StaticClass()));
				if (ensure(AttributeComponent))
				{
					float CurrentHealth = AttributeComponent->ReturnCurrentHealth();
					float MaxHealth = AttributeComponent->ReturnMaxHealth();
					bool LowHealth = CurrentHealth <= MaxHealth * LowHealthPercentage;

					BlackboardComponent->SetValueAsBool(IsLowHealth.SelectedKeyName, LowHealth);
					BlackboardComponent->SetValueAsBool(IsMaxHealth.SelectedKeyName, AttributeComponent->IsMaxHealth());
				}

			}
		}
	}
}
