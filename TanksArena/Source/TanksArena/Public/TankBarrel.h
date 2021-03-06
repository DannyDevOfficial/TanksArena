// This code is property of dannydev. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * Represents the barrel static mesh, will give control over it
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class TANKSARENA_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	/** Moves the barrel according to the relative speed
	* @param -1 to go down and +1 to go up
	*/
	void Elevate(float relativeSpeed);

private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float _maxDegreesPerSec = 10.0f;	// Max speed of movement in degrees per second

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float _maxElevationDegrees = 40.0f;	// Max elevation in degrees

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float _minElevationDegrees = 0.0f;	// Min elevation in degrees
};
