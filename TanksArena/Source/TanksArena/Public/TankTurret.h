// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * Represents turret static mesh, gives control over it
 */
UCLASS(meta = (BlueprintSpawnableComponent), hidecategories = ("Collision"))
class TANKSARENA_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	/** Rotates the turret according to the relative speed
	* @param -1 to go left and +1 to go right
	*/
	void RotateAround(float relativeSpeed);

private:
	UPROPERTY(EditAnywhere, Category = "Setup")
		float _maxDegreesPerSec = 10.0f;	// Max speed of movement in degrees per second
};
