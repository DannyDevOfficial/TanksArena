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
	// Sets default values for this component's properties
	UTankTrack();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	/** Sets the throttle for the tracks
	* @param throttle value to set
	*/
	UFUNCTION(BlueprintCallable, Category = "Input")
		void SetThrottle(float throttle) const;
	
private:
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComponent,
			FVector NormalImpulse,
			const FHitResult& Hit);

private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float _maxTrackDrivingForceN = 40000000.0f;	// The max amount of force in Newtons at which the track can move

};
