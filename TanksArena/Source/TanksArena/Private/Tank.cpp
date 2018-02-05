// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Projectile.h"

#include "Engine/World.h"
#include "Components/SceneComponent.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::AimAt(FVector hitPosition) const {
	// Delegate aiming to dedicated component
	_tankAimingComponent->AimAt(hitPosition, _launchSpeed);
}

void ATank::Fire() {
	// Get out if there is no barrel
	if (!_barrel || !_projectile)
		return;

	// Timer for firing projectiles
	if ((FPlatformTime::Seconds() - _lastTimeReloadedSecs) > _reloadTimeSecs) {
		// Spawn a projectile at the barrel's socket location and rotation
		FVector outProjectileSpawnLocation =
			_barrel->GetSocketLocation(FName(UTankAimingComponent::PROJECTILE_SPAWN_SOCKET));
		FRotator outProjectileSpawnRotation =
			_barrel->GetSocketRotation(FName(UTankAimingComponent::PROJECTILE_SPAWN_SOCKET));

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
