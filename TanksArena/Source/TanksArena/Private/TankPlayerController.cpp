// Fill out your copyright notice in the Description page of Project Settings.

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
		GetControlledTank()->FindComponentByClass<UTankAimingComponent>();

	if (aimingComp) {
		// Feed it to the event
		FoundAimingComponent(aimingComp);
	} else {
		UE_LOG(LogTemp, Warning, TEXT("Aiming component not found at begin play"));
	}
}

void ATankPlayerController::Tick(float DeltaTime) {
	// Call the parent's function
	Super::Tick(DeltaTime);

	// Aim the barrel at the crosshair
	AimAtCrosshair();
}


ATank* ATankPlayerController::GetControlledTank() const {
	// Cast the pawn component to a tank component since we know
	// that's what it is
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimAtCrosshair() {
	// Get out of here if there's no player controller
	if (!GetControlledTank())
		return;

	// Will store location in the world hit by the
	// crosshair
	FVector hitLocation;
	// If anything was hit
	if (GetSightRayHitLocation(hitLocation)) {
		// Aim at location
		GetControlledTank()->AimAt(hitLocation);
		// Aim the barrel at that point in the world
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& outHitLocation) const {
	// Find the location of the crosshair on the screen
	FVector2D crosshairScreenLocation;
	GetCrosshairScreenLocation(crosshairScreenLocation);

	// Deproject crosshair screen position to world direction
	FVector crosshairWorldDirection;

	if (!DeprojectCrosshairScreenPositionToWorld(crosshairScreenLocation,
		crosshairWorldDirection)) {
		UE_LOG(LogTemp, Error, TEXT("Unable to determine crosshair 3D location"));
	} else {
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
		ECollisionChannel::ECC_Visibility);

	outHitPosition = (objectHit == true) ? hitResult.Location : FVector(0.0f);

	return objectHit;
}