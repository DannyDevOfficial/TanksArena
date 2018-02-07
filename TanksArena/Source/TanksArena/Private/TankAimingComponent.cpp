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

	// Make it as if tanks fired a shot so they don't shoot as soon as the game starts
	_lastTimeReloadedSecs = FPlatformTime::Seconds();
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Set the current state to reloading if the timer is still running
	if ((FPlatformTime::Seconds() - _lastTimeReloadedSecs) < _reloadTimeSecs)
		_firingState = EFiringState::Reloading;
	else if (IsBarrelMoving())
		// Tank's aiming if barrel is moving
		_firingState = EFiringState::Aiming;
	else
		// Tank's firing if none of previous conditions were met
		_firingState = EFiringState::Locked;
}

EFiringState UTankAimingComponent::GetFiringState() const {
	return _firingState;
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

	// Only fire if tank's not reloading
	if (_firingState != EFiringState::Reloading) {
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

void UTankAimingComponent::AimAt(FVector hitWorldLocation) {
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
		// Set aim direction
		_aimDirection = outLaunchVelocity.GetSafeNormal();
		// Move the barrel!
		MoveBarrelAndTurret();
	}
}

void UTankAimingComponent::MoveBarrelAndTurret() const {
	// Get barrel current rotation
	FRotator barrelRotation = _barrel->GetForwardVector().Rotation();
	// Turn the aim direction vector into a rotation
	FRotator aimDirectionAsRotation = _aimDirection.Rotation();
	// Get the difference between aim direction rotation and barrel rotation
	// and this will be how much to rotate the barrel this frame
	FRotator deltaRotator = aimDirectionAsRotation - barrelRotation;

	// Used normalized rotators to always go the right way
	// Move barrel
	_barrel->Elevate(deltaRotator.GetNormalized().Pitch);
	// Move turret
	_turret->RotateAround(deltaRotator.GetNormalized().Yaw);
}

bool UTankAimingComponent::IsBarrelMoving() const {
	// Get out if there is no barrel
	if (!ensure(_barrel))
		return false;

	// Get the current forward vector for the barrel as a unit vector
	FVector barrelForwardDirectionUnitLength =
		_barrel->GetForwardVector().GetSafeNormal();
	// Make the aim direction of unit length
	FVector aimDirectionUnitLength = _aimDirection.GetSafeNormal();
	
	// Compare the two vectors
	// return true if they aren't equal
	// return false if they are equal
	return !barrelForwardDirectionUnitLength.Equals(aimDirectionUnitLength, 0.01f);
}
