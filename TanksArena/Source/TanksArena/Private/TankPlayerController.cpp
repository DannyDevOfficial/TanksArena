// This code is property of dannydev. All rights reserved.

#include "TankPlayerController.h"

#include "Tank.h"

#include "TankAimingComponent.h"
#include "GameFramework/Pawn.h"
#include "Engine/World.h"
#include "Camera/PlayerCameraManager.h"

void ATankPlayerController::BeginPlay() {
	// Execute what's in the parent class
	Super::BeginPlay();

	// Find aiming component
	auto aimingComp =
		GetPawn()->FindComponentByClass<UTankAimingComponent>();

	if (aimingComp)
		// Feed it to the event
		FoundAimingComponent(aimingComp);
}

void ATankPlayerController::SetPawn(APawn* InPawn) {
	// Very important to let the parent set the pawn
	Super::SetPawn(InPawn);

	// Make sure there is a pawn set
	if (InPawn) {
		// Cast the pawn to a Tank
		ATank* possessedTank = Cast<ATank>(InPawn);
		// Get out if there is no possessed tank
		if (!ensure(possessedTank))
			return;

		// Register for the OnDeath event
		possessedTank->OnDeath.AddUniqueDynamic(this,
			&ATankPlayerController::OnTankDeath);
	}
}

void ATankPlayerController::Tick(float DeltaTime) {
	// Call the parent's function
	Super::Tick(DeltaTime);

	// Aim the barrel at the crosshair
	AimAtCrosshair();
}

void ATankPlayerController::AimAtCrosshair() {
	// Get out if no pawn was found
	if (!GetPawn())
		return;

	// Find aiming component
	auto aimingComp =
		GetPawn()->FindComponentByClass<UTankAimingComponent>();

	// Get out of here if there's no aiming component
	if (!ensure(aimingComp))
		return;

	// Will store location in the world hit by the
	// crosshair
	FVector hitLocation;
	// If anything was hit
	if (GetSightRayHitLocation(hitLocation)) {
		// Aim at location
		aimingComp->AimAt(hitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& outHitLocation) const {
	// Find the location of the crosshair on the screen
	FVector2D crosshairScreenLocation;
	GetCrosshairScreenLocation(crosshairScreenLocation);

	// Deproject crosshair screen position to world direction
	FVector crosshairWorldDirection;

	if (DeprojectCrosshairScreenPositionToWorld(crosshairScreenLocation,
		crosshairWorldDirection)) {
		return LineTraceAlongCrosshairDirectionForHit(crosshairWorldDirection,
			outHitLocation);
	}

	// We should never get here
	return false;
}

void ATankPlayerController::GetCrosshairScreenLocation(FVector2D& outCrosshairScreenPosition) const {
	// Will hold viewport size
	int32 viewportXsize;
	int32 viewportYsize;
	// Get the viewport size
	GetViewportSize(viewportXsize, viewportYsize);

	// Will hold crosshair screen location
	outCrosshairScreenPosition =
		FVector2D(viewportXsize * _crossHairXLocation,
			viewportYsize * _crossHairYLocation);
}

bool ATankPlayerController::DeprojectCrosshairScreenPositionToWorld(FVector2D crosshairScreenPosition,
	FVector& outCrosshairWorldDirection) const {
	// Deproject crosshair screen position to a world 3D position
	FVector cameraWorldLocation;
	return DeprojectScreenPositionToWorld(crosshairScreenPosition.X, 
		crosshairScreenPosition.Y,
		cameraWorldLocation,
		outCrosshairWorldDirection);
}

bool ATankPlayerController::LineTraceAlongCrosshairDirectionForHit(FVector crosshairWorldDir,
	FVector& outHitPosition) const {
	// Store the necessary info
	FHitResult hitResult;
	FVector startLocation = PlayerCameraManager->GetCameraLocation();
	FVector endLocation = startLocation + (crosshairWorldDir * _lineTraceMaxRange);
	
	// Line trace along the crosshair direction and determine what was hit in the world
	// and set the hit location accordingly
	bool objectHit = GetWorld()->LineTraceSingleByChannel(hitResult,
		startLocation,
		endLocation,
		ECollisionChannel::ECC_Camera);

	outHitPosition = (objectHit == true) ? hitResult.Location : FVector(0.0f);

	return objectHit;
}

void ATankPlayerController::OnTankDeath() {
	// Become a spectator cause you're dead!
	StartSpectatingOnly();
}
