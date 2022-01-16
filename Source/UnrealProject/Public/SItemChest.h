#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SGameplayInterface.h"
#include "SItemChest.generated.h"

class UStaticMeshComponent;

/*
 * Item chest actor that implements ISGameplayInterface for InteractionComponent
 * communication.
 */

UCLASS()
class UNREALPROJECT_API ASItemChest : public AActor, public ISGameplayInterface
{
	GENERATED_BODY()

#pragma region Methods
	void Interact_Implementation(APawn* InstigatorPawn) override;

public:	
	// Sets default values for this actor's properties
	ASItemChest();
#pragma endregion Methods

#pragma region Properties
public:
	UPROPERTY(EditAnywhere)
	float TargetPitch;

protected:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* LidMesh;
#pragma endregion Properties
};
