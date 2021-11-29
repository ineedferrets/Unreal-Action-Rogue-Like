// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGameplayInterface.h"
#include "GameFramework/Actor.h"
#include "SHealthPotion.generated.h"

class UStaticMeshComponent;

UCLASS()
class UNREALPROJECT_API ASHealthPotion : public AActor, public ISGameplayInterface
{
	GENERATED_BODY()

	void Interact_Implementation(APawn* InstigatorPawn) override;
	
public:	
	// Sets default values for this actor's properties
	ASHealthPotion();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void OnTimer_HealthInactiveElapsed();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:

	UPROPERTY(EditAnywhere)
	float HealthIncrease = 20.0f;

	UPROPERTY(EditAnywhere)
	float RespawnTimer = 10.0f;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere)
	bool bCanBeInteractedWith = true;
private:
	FTimerHandle TimerHandle_HealthInactive;

};
