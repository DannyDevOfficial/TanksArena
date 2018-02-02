// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * Represents track static mesh, gives control over it
 */
UCLASS(meta = (BlueprintSpawnableComponent), hidecategories = ("Collision"))
class TANKSARENA_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	/** Sets the throttle for the tracks
	* @param throttle value to set
	*/
	UFUNCTION(BlueprintCallable, Category = "Input")
		void SetThrottle(float throttle) const;
	
};
