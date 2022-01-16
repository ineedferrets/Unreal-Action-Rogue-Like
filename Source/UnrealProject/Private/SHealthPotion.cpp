#include "SHealthPotion.h"
#include "SAttributeComponent.h"

// Implement components and set default values.
ASHealthPotion::ASHealthPotion()
{
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BaseMesh->SetupAttachment(RootComponent);

}


void ASHealthPotion::Interact_Implementation(APawn* InstigatorPawn)
{
	if (!ensure(InstigatorPawn))
	{
		return;
	}

	USAttributeComponent* AttributeComponent = Cast<USAttributeComponent>(InstigatorPawn->GetComponentByClass(USAttributeComponent::StaticClass()));

	if (ensure(AttributeComponent) && !AttributeComponent->IsMaxHealth())
	{
		if (AttributeComponent->ApplyHealthChange(this, HealthIncrease))
		{
			HideAndCooldownPowerUp();
		}
	}
}
