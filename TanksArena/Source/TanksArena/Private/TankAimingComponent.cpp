// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"

#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

#include "TankBarrel.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::AimAt(FVector hitWorldLocation, float launchSpeed) const {
	// Get out if there's no barrel
	if (!_barrel)
		return;

	// Variables for the launch direction function
	FVector outLaunchVelocity;
	FVector startLaunchLocation = _barrel->GetSocketLocation(PROJECTILE_SPAWN_SOCKET);
	// Calculate the projectile velocity then store it in the out param
	bool aimSoultionFound = UGameplayStatics::SuggestProjectileVelocity(this,
		outLaunchVelocity,
		startLaunchLocation,
		hitWorldLocation,
		launchSpeed,
		false,
		0.0f,
		0.0f,
		ESuggestProjVelocityTraceOption::DoNotTrace);
	// Aim solution was found
	if (aimSoultionFound) {
		// The launch succeded
		// Get aim direction
		FVector projectileAimDirection = outLaunchVelocity.GetSafeNormal();
		// Log out the aiming point
		UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s"),
			*GetOwner()->GetName(),
			*projectileAimDirection.ToString());

		// Move the barrel!
		MoveBarrel(projectileAimDirection);
	}
}

void UTankAimingComponent::SetBarrel(UTankBarrel* barrel) {
	// Get out if it's null
	if (!barrel)
		return;

	// Set the barrel
	_barrel = barrel;
}

void UTankAimingComponent::MoveBarrel(FVector aimDirection) const {
	// Get barrel current rotation
	FRotator barrelRotation = _barrel->GetForwardVector().Rotation();
	// Turn the aim direction vector into a rotation
	FRotator aimDirectionAsRotation = aimDirection.Rotation();
	// Get the difference between aim direction rotation and barrel rotation
	// and this will be how much to rotate the barrel this frame
	FRotator deltaRotator = aimDirectionAsRotation - barrelRotation;

	// Move barrel
	_barrel->Elevate(5.0f);
}