// This code is property of dannydev. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * Represents turret static mesh, gives control over it
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class TANKSARENA_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	/** Rotates the turret according to the relative speed
	* @param -1 to go left and +1 to go right
	*/
	void RotateAround(float relativeSpeed);

private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float _maxDegreesPerSec = 25.0f;	// Max speed of movement in degrees per second
};
