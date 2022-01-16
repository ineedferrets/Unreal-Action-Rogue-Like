#include "SPowerUpActor.h"
#include "Components/SphereComponent.h"

#pragma region Initialisation
// Sets default values
ASPowerUpActor::ASPowerUpActor()
{
	SphereComponent = CreateAbstractDefaultSubobject<USphereComponent>("SphereComponent");
	SphereComponent->SetCollisionProfileName("Powerup");
	RootComponent = SphereComponent;
}
#pragma endregion Initialisation

void ASPowerUpActor::Interact_Implementation(APawn* InstigatorPawn)
{
	// Logic in derived classes!
}

#pragma region General PowerUp Functionality
void ASPowerUpActor::ShowPowerUp()
{
	SetPowerUpState(true);
}

void ASPowerUpActor::HideAndCooldownPowerUp()
{
	SetPowerUpState(false);

	GetWorldTimerManager().SetTimer(TimerHandle_RespawnTimer, this, &ASPowerUpActor::ShowPowerUp, RespawnTime);
}

void ASPowerUpActor::SetPowerUpState(bool bNewIsActive)
{
	SetActorEnableCollision(bNewIsActive);

	RootComponent->SetVisibility(bNewIsActive, true);
}
#pragma endregion General PowerUpFunctionality