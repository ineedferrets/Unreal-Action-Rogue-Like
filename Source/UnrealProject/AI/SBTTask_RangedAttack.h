#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "SBTTask_RangedAttack.generated.h"

/**
 * Behaviour tree task that fires projectiles with some amount of spread.
 */
UCLASS()
class UNREALPROJECT_API USBTTask_RangedAttack : public UBTTaskNode
{
	GENERATED_BODY()

#pragma region Methods
public:
	USBTTask_RangedAttack();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
#pragma endregion Methods

#pragma region Properties
protected:
	UPROPERTY(EditAnywhere, Category = "AI")
	float MaxBulletSpread;

	UPROPERTY(EditAnywhere, Category = "AI")
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(BlueprintReadOnly, Category = "AI")
	FName MuzzleName = "Muzzle_01";
#pragma endregion Properties
};
