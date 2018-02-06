// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"

#include "TankTrack.h"

void UTankMovementComponent::Initialize(UTankTrack* leftTrack, UTankTrack* rightTrack) {
	// Get out if the references are null
	if (!ensure(leftTrack && rightTrack))
		return;

	// Set the member variables
	_leftTrack = leftTrack;
	_rightTrack = rightTrack;
}

void UTankMovementComponent::IntendMoveForward(float theThrow) const {
	// Get out if the references are null
	if (!ensure(_leftTrack && _rightTrack))
		return;

	// Set the throttle for the tracks based on
	// the argument passed in
	_leftTrack->SetThrottle(theThrow);
	_rightTrack->SetThrottle(theThrow);
}

void UTankMovementComponent::IntendTurnRight(float theThrow) const {
	// Get out if the references are null
	if (!ensure(_leftTrack && _rightTrack))
		return;

	// Set the throttle for the tracks based on
	// the argument passed in
	_leftTrack->SetThrottle(theThrow);
	_rightTrack->SetThrottle(-theThrow);
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity,
	bool bForceMaxSpeed) {
	// Get the tank's forward vector as a unit vector
	FVector tankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	// Make the movement intention of the tank into a unit vector
	FVector AItankForwardIntention = MoveVelocity.GetSafeNormal();

	// Take the dot product between the two to find out how parallel these two are
	// and move to make them parallel
	float forwardThrow = FVector::DotProduct(tankForward, AItankForwardIntention);
	// Take the cross product between the two to find out how perpendicular these two are
	// and turn to make the AI face the player
	FVector crossedVector = FVector::CrossProduct(tankForward, AItankForwardIntention);

	// Move the AI tank
	IntendMoveForward(forwardThrow);
	IntendTurnRight(crossedVector.Z);
}
