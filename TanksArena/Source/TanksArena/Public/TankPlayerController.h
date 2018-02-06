// This code is property of dannydev. All rights reserved.

#pragma once

class UTankAimingComponent;

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * Controls the tank used by the player
 */
UCLASS()
class TANKSARENA_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	/**
	* Called once at the start
	*/
	virtual void BeginPlay() override;

	/**
	* Runs once every frame
	*/
	virtual void Tick(float DeltaTime) override;

protected:
	/**
	* Event that fires when an aiming component is found
	*/
	UFUNCTION(BlueprintImplementableEvent, Category = "Event")
		void FoundAimingComponent(UTankAimingComponent* aimingComponent);

private:
	/** Makes the tank move the barrel towards the point
	* where the crosshair intersects the world
	*/
	void AimAtCrosshair();

	/** Gets location in the world where the crosshair is intersecting
	* a point in the world.
	* @param Vector that will contain the point hit in the world.
	* @return Whether or not a part of the map was hit.
	*/
	bool GetSightRayHitLocation(FVector& outHitLocation) const;

	/** Calculates the viewport size and from that it gets the crosshair position on the screen.
	* @param Vector that will contain the crosshair location on the screen.
	*/
	void GetCrosshairScreenLocation(FVector2D& outCrosshairScreenPosition) const;

	/** Deprojects the crosshair screen position to a world position.
	* @param Vector that will contain the crosshair location on the screen.
	* @param Vector that will contain the crosshair direction in the world.
	* @return True if it was able to determine a world position.
	*/
	bool DeprojectCrosshairScreenPositionToWorld(FVector2D crosshairScreenPosition,
		FVector& outCrosshairWorldDirection) const;

	/** Traces a line along the crosshair direction and determines if anything
	* was hit in a max range.
	* @param Vector that will contain the crosshair direction in the world.
	* @param Vector that will contain the location in the world of the hit object.
	* @return True if an object was hit.
	*/
	bool LineTraceAlongCrosshairDirectionForHit(FVector crosshairWorldDir,
		FVector& outHitPosition) const;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float _crossHairXLocation = 0.5f;		// Location of the crosshair on the viewport horizontally,
												// meaning it's in the middle of the viewport

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float _crossHairYLocation = 0.33333f;	// Location of the crosshair on the viewport vertically,
												// meaning it's a third of the way down the viewport

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float _lineTraceMaxRange = 10000.0f;	// The max range for the line trace
};
