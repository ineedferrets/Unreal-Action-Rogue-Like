// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SPowerUPActor.h"
#include "SHealthPotion.generated.h"

class UStaticMeshComponent;

UCLASS()
class UNREALPROJECT_API ASHealthPotion : public ASPowerUPActor
{
	GENERATED_BODY()

	void Interact_Implementation(APawn* InstigatorPawn) override;
	
public:	
	// Sets default values for this actor's properties
	ASHealthPotion();

protected:

	UPROPERTY(EditAnywhere)
	float HealthIncrease = 20.0f;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;

};
