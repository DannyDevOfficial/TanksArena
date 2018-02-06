// This code is property of dannydev. All rights reserved.

#include "TankTrack.h"

void UTankTrack::SetThrottle(float throttle) const {
	// Get the force vector to apply to the tracks
	FVector forceVectorToApplyToTracks =
		GetForwardVector() * _maxTrackDrivingForceN * throttle;

	// Get the root component in the tracks' hierarchy
	UPrimitiveComponent* rootComponent =
		Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	// Apply force on root if it was found
	if (rootComponent) {
		// Get the location where to apply force
		FVector forceLocation = GetComponentLocation();
		rootComponent->AddForceAtLocation(forceVectorToApplyToTracks, forceLocation);
	}
}