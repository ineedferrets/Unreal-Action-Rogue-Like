// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SAttributeComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnHealthChanged, AActor*, InstigatorActor, USAttributeComponent*,
                                              OwningComponent, float, NewHealth, float, Delta);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALPROJECT_API USAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	static USAttributeComponent* GetAttributes(AActor* FromActor);

	UFUNCTION(BlueprintCallable, Category = "Attributes", meta = (DisplayName = "Is Alive"))
	static bool IsActorAlive(AActor* Actor);

	// Sets default values for this component's properties
	USAttributeComponent();

protected:

	// EditAnywhere - Edit in BP Editor and per-instance in level.
	// VisibleAnywhere - "Read-only" in editor and level. (Use for components)
	// EditDefaultsOnly - Hide variable per-instance, edit in BP editor only.
	// VisibleDefaultsOnly - "Read-only" access in BP editor only.
	// EditInstanceOnly - Allow only editing of instance in level.
	// --
	// BlueprintReadOnly - "Read-only" in the Blueprint scripting (does not affect "Details" pane).
	// BlueprintReadWrite - Read-write access in blueprints.
	// --
	// Category = "" - Heading in detail panels and blueprint context menu it will appear under.

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
	float Health;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
	float MaxHealth = 100.0f;

public:

	UFUNCTION(BlueprintCallable)
	bool IsAlive() const;

	UFUNCTION(BlueprintCallable)
	bool IsMaxHealth() const;

	UFUNCTION(BlueprintCallable)
	float ReturnCurrentHealth() const;

	UFUNCTION(BlueprintCallable)
	float ReturnMaxHealth() const;

	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	bool ApplyHealthChange(AActor* InstigatorActor, float Delta);

};
