// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"

void UTankBarrel::Elevate(float degreesPerSec) const {
	// Move the barrel the given amount of degrees per second
	UE_LOG(LogTemp,
		Warning,
		TEXT("Barrel moved %f degrees per second"),
		degreesPerSec);
}