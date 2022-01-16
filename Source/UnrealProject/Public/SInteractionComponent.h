#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SInteractionComponent.generated.h"

/*
 * Actor component that implements interaction functionality for a player.
 */

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALPROJECT_API USInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

#pragma region Methods
public:
	USInteractionComponent();

	void PrimaryInteract();
#pragma endregion Methods
};
