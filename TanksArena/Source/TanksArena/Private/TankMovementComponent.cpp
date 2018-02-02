// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"

#include "TankTrack.h"

void UTankMovementComponent::Initialize(UTankTrack* leftTrack, UTankTrack* rightTrack) {
	// Get out if the references are null
	if (!leftTrack || !rightTrack)
		return;

	// Set the member variables
	_leftTrack = leftTrack;
	_rightTrack = rightTrack;
}

void UTankMovementComponent::IntendMoveForward(float theThrow) const {
	// Set the throttle for the tracks based on
	// the argument passed in
	_leftTrack->SetThrottle(theThrow);
	_rightTrack->SetThrottle(theThrow);
}
