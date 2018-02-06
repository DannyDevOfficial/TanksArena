// This code is property of dannydev. All rights reserved.

#include "TankTrack.h"

#include "Engine/World.h"

UTankTrack::UTankTrack() {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::BeginPlay() {
	Super::BeginPlay();

	// Register delegate for OnHit() events
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UTankTrack::ApplySidewaysForce() {
	// Calculate the slippage speed of the tank
	float slippageSpeed =
		FVector::DotProduct(GetComponentVelocity(), GetRightVector());
	// Calculate the acceleration needed to correct that slippage
	FVector correctionAcceleration =
		(-slippageSpeed / GetWorld()->GetDeltaSeconds()) *
		GetRightVector();
	// Caculate the force to apply in the opposite direction of the slippage
	// Divide it by two cause there are two tracks or we would apply the whole force on both the tracks
	auto tankRootComponentInHierarchy = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	FVector correctionForce = (tankRootComponentInHierarchy->GetMass() * correctionAcceleration) / 2;
	// Apply the force to the tank
	tankRootComponentInHierarchy->AddForce(correctionForce);
}

void UTankTrack::SetThrottle(float throttle) {
	// Set the current throttle
	_currentThrottle =
		FMath::Clamp(_currentThrottle + throttle, -2.0f, 2.0f);
}

void UTankTrack::DriveTrack() const {
	// Get the force vector to apply to the tracks
	FVector forceVectorToApplyToTracks =
		GetForwardVector() * _maxTrackDrivingForceN * _currentThrottle;

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

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComponent,
	FVector NormalImpulse,
	const FHitResult& Hit) {
	DriveTrack();
	ApplySidewaysForce();
	// Reset current throttle to zero so tank doesn't keep 
	// going after releasing the movement button
	_currentThrottle = 0.0f;
}
