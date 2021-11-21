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

public:

	UFUNCTION(BlueprintCallable)
	bool IsAlive() const;

	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	bool ApplyHealthChange(float Delta);

};
