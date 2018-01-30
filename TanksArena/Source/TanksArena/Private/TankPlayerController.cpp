// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

#include "Tank.h"
#include "GameFramework/Pawn.h"
#include "Classes/Engine/World.h"

void ATankPlayerController::BeginPlay() {
	// Execute what's in the parent class
	Super::BeginPlay();

	// Log to console only if there is a valid pointer
	ATank* posessedTank = GetControlledTank();
	if (posessedTank) {
		UE_LOG(LogTemp, Warning, TEXT("Posessed Tank: %s"), *posessedTank->GetName());
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("There is no posessed tank!"));
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
		// Aim the barrel at that point in the world
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const {
	// Will hold viewport size
	int32 viewportXsize;
	int32 viewportYsize;
	// Get the viewport size
	GetViewportSize(viewportXsize, viewportYsize);

	// Will hold crosshair screen location
	FVector2D crosshairScreenLocation =
		FVector2D(viewportXsize * _crossHairXLocation,
			viewportYsize * _crossHairYLocation);

	return false;
}
