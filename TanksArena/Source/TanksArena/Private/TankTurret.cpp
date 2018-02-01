// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"

#include "Engine/World.h"

void UTankTurret::RotateAround(float relativeSpeed) {
	// Clamp the relative speed between -1 and 1
	relativeSpeed = FMath::Clamp(relativeSpeed, -1.0f, 1.0f);

	// Get change in rotation frame independent
	float rotationalChange = relativeSpeed * _maxDegreesPerSec * GetWorld()->DeltaTimeSeconds;
	// Get the rotation
	float rotation = RelativeRotation.Yaw + rotationalChange;

	// Set the rotation for the barrel
	SetRelativeRotation(FRotator(0.0f, rotation, 0.0f));
}