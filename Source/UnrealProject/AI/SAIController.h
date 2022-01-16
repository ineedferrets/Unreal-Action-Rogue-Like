// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SAIController.generated.h"

class UBehaviorTree;

/**
 *	Base AI controller for this project's game.
 */

UCLASS()
class UNREALPROJECT_API ASAIController : public AAIController
{
	GENERATED_BODY()

#pragma region Methods
protected:
	virtual void BeginPlay() override;
#pragma endregion Methods

#pragma region Properties
protected:
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UBehaviorTree* BehaviorTree;
#pragma endregion Properties
};
