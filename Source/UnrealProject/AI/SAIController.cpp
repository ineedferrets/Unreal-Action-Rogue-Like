// Fill out your copyright notice in the Description page of Project Settings.


#include "SAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void ASAIController::BeginPlay()
{
	Super::BeginPlay();

	if(ensureMsgf(BehaviorTree,
		TEXT("Behaviour Tree is nullptr! Please assign BehaviourTree in your AI Controller.")))
	{
		RunBehaviorTree(BehaviorTree);
	}
}


