// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"

#include "Engine/World.h"

void UTankBarrel::Elevate(float relativeSpeed) {
	// Clamp the relative speed between -1 and 1
	relativeSpeed = FMath::Clamp(relativeSpeed, -1.0f, 1.0f);

	// Get change in elevation frame independent
	float elevationChange = relativeSpeed * _maxDegreesPerSec * GetWorld()->DeltaTimeSeconds;
	// Get the unclamped elevation
	float unclampedElevation = RelativeRotation.Pitch + elevationChange;
	// Clamp the elevation between our min and max values
	float clampedElevation = FMath::Clamp(unclampedElevation, _minElevationDegrees, _maxElevationDegrees);
	
	// Set the rotation for the barrel
	SetRelativeRotation(FRotator(clampedElevation, 0.0f, 0.0f));
}