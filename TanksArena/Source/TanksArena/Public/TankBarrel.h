// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * Represents the barrel static mesh, will give control over it
 */
UCLASS(meta = (BlueprintSpawnableComponent), hidecategories = ("Collision"))
class TANKSARENA_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	/** Moves the barrel a given amount of degrees per second
	* @param Barrel will be moved this amount of degrees per second
	*/
	void Elevate(float relativeSpeed) const;

private:
	UPROPERTY(EditAnywhere, Category = "Setup")
		float _maxDegreesPerSec = 100.0f;	// Max speed of movement in degrees per second

	UPROPERTY(EditAnywhere, Category = "Setup")
		float _maxElevationDegrees = 50.0f;	// Max elevation in degrees

	UPROPERTY(EditAnywhere, Category = "Setup")
		float _minElevationDegrees = 0.0f;	// Min elevation in degrees
};
