#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SWorldUserWidget.generated.h"

class USizeBox;

/**
 * A widget that will appear on an attached actor.
 */
UCLASS()
class UNREALPROJECT_API USWorldUserWidget : public UUserWidget
{
	GENERATED_BODY()

#pragma region Methods
protected:
	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
#pragma endregion Methods

#pragma region Properties
protected:
	UPROPERTY(meta = (BindWidget))
	USizeBox* ParentSizeBox;

public:
	UPROPERTY(EditAnywhere, Category = "UI")
	FVector WorldOffset;

	UPROPERTY(BlueprintReadOnly, Category = "UI")
	AActor* AttachedActor;
#pragma endregion Properties
};
