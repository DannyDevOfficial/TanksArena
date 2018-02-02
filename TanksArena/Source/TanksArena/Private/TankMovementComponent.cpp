// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"

void UTankMovementComponent::IntendMoveForward(float theThrow) const {
	// Log out the throttle for now
	UE_LOG(LogTemp, Warning, TEXT("throw is: %f"), theThrow);
}
