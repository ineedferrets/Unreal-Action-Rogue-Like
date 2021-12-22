// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGameplayInterface.h"
#include "GameFramework/Actor.h"
#include "SPowerUPActor.generated.h"

class USphereComponent;


UCLASS()
class UNREALPROJECT_API ASPowerUPActor : public AActor, public ISGameplayInterface
{
	GENERATED_BODY()

	void Interact_Implementation(APawn* InstigatorPawn) override;
	
public:	
	// Sets default values for this actor's properties
	ASPowerUPActor();

protected:
	void ShowPowerup();

	void HideAndCooldownPowerup();

	void SetPowerupState(bool bNewIsActive);

protected:
	UPROPERTY(VisibleAnywhere)
	USphereComponent* SphereComponent;

	UPROPERTY(EditAnywhere, Category = "Power Up")
	float RespawnTime = 10.0f;

	FTimerHandle TimerHandle_RespawnTimer;

};
