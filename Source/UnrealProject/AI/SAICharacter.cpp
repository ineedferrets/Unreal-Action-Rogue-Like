// Fill out your copyright notice in the Description page of Project Settings.


#include "SAICharacter.h"
#include "Perception/PawnSensingComponent.h"
#include "AIController.h"
#include "DrawDebugHelpers.h"
#include "BehaviorTree/BlackboardComponent.h"

// Sets default values
ASAICharacter::ASAICharacter()
{
	PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>("PawnSensingComponent");
}

void ASAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	PawnSensingComponent->OnSeePawn.AddDynamic(this, &ASAICharacter::OnPawnSeen);
}


void ASAICharacter::OnPawnSeen(APawn* Pawn)
{
	AAIController* AIController = Cast<AAIController>(GetController());
	if (AIController)
	{
		UBlackboardComponent* BlackboardComponent = AIController->GetBlackboardComponent();

		BlackboardComponent->SetValueAsObject("TargetActor", Pawn);

		DrawDebugString(GetWorld(), GetActorLocation(), "PLAYER SPOTTED", nullptr, FColor::White, 4.0f, true);
	}
}

