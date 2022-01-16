#include "SAIController.h"
#include "Kismet/GameplayStatics.h"

#pragma region Initialisation
void ASAIController::BeginPlay()
{
	Super::BeginPlay();

	if(ensureMsgf(BehaviorTree,
		TEXT("Behaviour Tree is nullptr! Please assign BehaviourTree in your AI Controller.")))
	{
		RunBehaviorTree(BehaviorTree);
	}
}
#pragma endregion Initialisation