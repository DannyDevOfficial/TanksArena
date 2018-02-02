// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

void UTankTrack::SetThrottle(float throttle) const {
	// Log out the throttle for now
	UE_LOG(LogTemp, Warning, TEXT("%s throttle: %f"), *GetName(), throttle);
}