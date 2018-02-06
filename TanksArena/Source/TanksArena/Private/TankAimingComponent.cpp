// This code is property of dannydev. All rights reserved.

#include "TankAimingComponent.h"

#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Components/SceneComponent.h"

#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"

// Init static member
const FName UTankAimingComponent::PROJECTILE_SPAWN_SOCKET = "Projectile Spawn";

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UTankAimingComponent::Initialize(UTankTurret* tankTurret,
	UTankBarrel* tankBarrel) {
	// Get out if nothing was passed in
	if (!ensure(tankTurret && tankBarrel))
		return;

	// Set the members
	_turret = tankTurret;
	_barrel = tankBarrel;
}

void UTankAimingComponent::Fire() {
	// Get out if there is no barrel
	if (!ensure(_barrel && _projectile))
		return;

	// Timer for firing projectiles
	if ((FPlatformTime::Seconds() - _lastTimeReloadedSecs) > _reloadTimeSecs) {
		// Spawn a projectile at the barrel's socket location and rotation
		FVector outProjectileSpawnLocation =
			_barrel->GetSocketLocation(PROJECTILE_SPAWN_SOCKET);
		FRotator outProjectileSpawnRotation =
			_barrel->GetSocketRotation(PROJECTILE_SPAWN_SOCKET);

		AProjectile* newProjectile =
			GetWorld()->SpawnActor<AProjectile>(_projectile,
				outProjectileSpawnLocation,
				outProjectileSpawnRotation);

		// Call the launch function from the projectile
		newProjectile->Launch(_launchSpeed);

		// Update the last time barrel reloaded
		_lastTimeReloadedSecs = FPlatformTime::Seconds();
	}
}

void UTankAimingComponent::AimAt(FVector hitWorldLocation) const {
	// Get out if there's no barrel
	if (!ensure(_barrel && _turret))
		return;

	// Variables for the launch direction function
	FVector outLaunchVelocity;
	FVector startLaunchLocation = _barrel->GetSocketLocation(PROJECTILE_SPAWN_SOCKET);
	// Calculate the projectile velocity then store it in the out param
	bool aimSoultionFound = UGameplayStatics::SuggestProjectileVelocity(this,
		outLaunchVelocity,
		startLaunchLocation,
		hitWorldLocation,
		_launchSpeed,
		false,
		0.0f,
		0.0f,
		ESuggestProjVelocityTraceOption::DoNotTrace);
	// Aim solution was found
	if (aimSoultionFound) {
		// The launch succeded
		// Get aim direction
		FVector projectileAimDirection = outLaunchVelocity.GetSafeNormal();
		// Move the barrel!
		MoveBarrelAndTurret(projectileAimDirection);
	}
}

void UTankAimingComponent::MoveBarrelAndTurret(FVector aimDirection) const {
	// Get barrel current rotation
	FRotator barrelRotation = _barrel->GetForwardVector().Rotation();
	// Turn the aim direction vector into a rotation
	FRotator aimDirectionAsRotation = aimDirection.Rotation();
	// Get the difference between aim direction rotation and barrel rotation
	// and this will be how much to rotate the barrel this frame
	FRotator deltaRotator = aimDirectionAsRotation - barrelRotation;

	// Move barrel
	_barrel->Elevate(deltaRotator.Pitch);
	// Move turret
	_turret->RotateAround(deltaRotator.Yaw);
}
