// This code is property of dannydev. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * Represents track static mesh, gives control over it
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class TANKSARENA_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	/** Sets the throttle for the tracks
	* @param throttle value to set
	*/
	UFUNCTION(BlueprintCallable, Category = "Input")
		void SetThrottle(float throttle) const;
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float _maxTrackDrivingForceN = 40000000.0f;	// The max amount of force in Newtons at which the track can move

};
