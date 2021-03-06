#pragma region Includes
#include "SCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "DrawDebugHelpers.h"
#include "SInteractionComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "SAttributeComponent.h"
#pragma endregion Includes

#pragma region Console Variables
static TAutoConsoleVariable<bool> CVarDebugDrawView(TEXT("jh.PlayerViewDebugDraw"), false, TEXT("Enable Debug Arrows for Player and Character View."), ECVF_Cheat);
#pragma endregion Console Variables

#pragma region Initialisation
// Set default values and implement components
ASCharacter::ASCharacter()
{
 	// Set this character to call Tick() every frame.
 	// You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set rotation of character based on movement rather than camera (upper body rotated through animation blueprint).
	GetCharacterMovement()->bOrientRotationToMovement = true;

	bUseControllerRotationYaw = false;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);

	InteractionComponent = CreateDefaultSubobject<USInteractionComponent>("InteractionComponent");
	AttributeComponent = CreateDefaultSubobject<USAttributeComponent>("AttributeComponent");
}

// Bind events post construction.
void ASCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	AttributeComponent->OnHealthChanged.AddDynamic(this, &ASCharacter::OnHealthChanged);
}

// Called to bind functionality to input
void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Map movement
	PlayerInputComponent->BindAxis("MoveForward", this, &ASCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASCharacter::MoveRight);

	// Map camera manipulations
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	// Map actions
	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &ASCharacter::PrimaryAttack);
	PlayerInputComponent->BindAction("SecondaryAttack", IE_Pressed, this, &ASCharacter::SecondaryAttack);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASCharacter::Jump);
	PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &ASCharacter::PrimaryInteract);
	PlayerInputComponent->BindAction("Teleport", IE_Pressed, this, &ASCharacter::Teleport);
}
#pragma endregion Initialisation

void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Rotation Visualization
	bool bDebugDrawView = CVarDebugDrawView.GetValueOnGameThread();
	if (bDebugDrawView)
	{
		const float DrawScale = 100.0f;
		const float Thickness = 5.0f;
		FVector LineStart = GetActorLocation();
		LineStart += GetActorRightVector() * 100.0f;

		// Draw Actor's Direction
		FVector ActorDirection_LineEnd = LineStart + (GetActorForwardVector() * 100.0f);
		DrawDebugDirectionalArrow(GetWorld(), LineStart, ActorDirection_LineEnd, DrawScale, FColor::Yellow, false, 0.0f, 0, Thickness);

		// Draw 'Controller' Rotation ('PlayerController' that 'possessed' this character)
		FVector ControllerDirection_LineEnd = LineStart + (GetControlRotation().Vector() * 100.0f);
		DrawDebugDirectionalArrow(GetWorld(), LineStart, ControllerDirection_LineEnd, DrawScale, FColor::Green, false, 0.0f, 0, Thickness);
	}
}

#pragma region Movement
void ASCharacter::MoveForward(float value)
{
	FRotator ControlRotation = GetControlRotation();
	ControlRotation.Pitch = 0.0f;
	ControlRotation.Roll = 0.0f;

	AddMovementInput(ControlRotation.Vector(), value);
}

void ASCharacter::MoveRight(float value)
{
	FRotator ControlRotation = GetControlRotation();
	ControlRotation.Pitch = 0.0f;
	ControlRotation.Roll = 0.0f;

	FVector RightVector = FRotationMatrix(ControlRotation).GetScaledAxis(EAxis::Y);

	AddMovementInput(RightVector, value);
}
#pragma endregion Movement

#pragma region Abilities
void ASCharacter::PrimaryAttack()
{
	PlayAnimMontage(AttackAnim);

	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &ASCharacter::PrimaryAttack_TimeElapsed, 0.2f);
}

void ASCharacter::PrimaryAttack_TimeElapsed()
{
	SpawnProjectile(PrimaryProjectileClass);
}

void ASCharacter::SecondaryAttack()
{
	PlayAnimMontage(AttackAnim);

	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &ASCharacter::SecondaryAttack_TimeElapsed, 0.2f);
}

void ASCharacter::SecondaryAttack_TimeElapsed()
{
	SpawnProjectile(SecondaryProjectileClass);
}

void ASCharacter::SpawnProjectile(TSubclassOf<AActor> ProjectileClass)
{
	// Check that an appropriate Projectile Class is used.
	// NOTE: ensureAlways pauses game in debug/engine always. Not just once like 'ensure'. Also is ignored
	//		 in game build.
	if (ensureAlways(ProjectileClass))
	{
		// Get spawn point of projectile from Muzzle socket.
		FTransform SpawnTM = FTransform(GetControlRotation(), GetMesh()->GetSocketLocation("Muzzle_01"));

		// Set to query World Dynamic, World Static, Physics Body, and Pawns
		FCollisionObjectQueryParams ObjectQueryParams;
		ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
		ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldStatic);
		ObjectQueryParams.AddObjectTypesToQuery(ECC_PhysicsBody);
		ObjectQueryParams.AddObjectTypesToQuery(ECC_Pawn);

		// Line Trace from Camera
		FHitResult Hit;
		FVector Start = CameraComp->GetComponentLocation();
		Start += CameraComp->GetComponentRotation().Vector() * 100;
		FVector End = Start + (CameraComp->GetComponentRotation().Vector() * 5000);
		bool bBlockingHit = GetWorld()->LineTraceSingleByObjectType(Hit, Start, End, ObjectQueryParams);
		FColor LineColor = bBlockingHit ? FColor::Green : FColor::Red;
		DrawDebugLine(GetWorld(), Start, End, LineColor, false, 2.0f, 0, 2.0f);

		// Replace end with impact point if trace hits something
		if (bBlockingHit)
			End = Hit.ImpactPoint;

		// Set spawn parameters
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Instigator = this;

		// Update spawn rotation
		FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(SpawnTM.GetLocation(), End);
		SpawnTM.SetRotation(TargetRotation.Quaternion());

		// Spawn projectile
		AActor* Projectile = GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);

		// Spawn Emitter
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), MuzzleFlash, SpawnTM);

		// Draw trace from hand (the path the projectile should take)
		DrawDebugLine(GetWorld(), SpawnTM.GetLocation(), SpawnTM.GetLocation() + (1000 * TargetRotation.Vector()), FColor::Blue, false, 2.0f, 0, 2.0f);
	}
}

void ASCharacter::PrimaryInteract()
{
	// Check interaction component is present
	if (ensureAlways(InteractionComponent))
	{
		InteractionComponent->PrimaryInteract();
	}
}

void ASCharacter::Teleport()
{
	PlayAnimMontage(AttackAnim);

	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &ASCharacter::Teleport_TimeElapsed, 0.2f);
}

void ASCharacter::Teleport_TimeElapsed()
{
	SpawnProjectile(TeleportProjectileClass);
}
#pragma endregion Abilities

#pragma region Health
void ASCharacter::OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComponent, float NewHealth, float Delta)
{
	// If health change is damaging.
	if (Delta < 0)
	{
		AActor* ThisActor = Cast<AActor>(this);
		UStaticMeshComponent* MeshComponent = FindComponentByClass<UStaticMeshComponent>();
		if (MeshComponent)
			MeshComponent->SetScalarParameterValueOnMaterials("HitFlashTime", GetWorld()->TimeSeconds);

		// If health change kills player.
		if (NewHealth <= 0.0f)
		{
			APlayerController* PlayerController = Cast<APlayerController>(GetController());
			DisableInput(PlayerController);
		}
	}
}

// NOTE: Currently only usable through console. Could be new ability?
void ASCharacter::HealSelf(float Amount /* = 100 */)
{
	AttributeComponent->ApplyHealthChange(this, Amount);
}
#pragma endregion Health

FVector ASCharacter::GetPawnViewLocation() const
{
	return CameraComp->GetComponentLocation();
}
