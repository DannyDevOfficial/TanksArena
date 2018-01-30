// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class ATank;

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
	
private:
	// Called once at the start
	virtual void BeginPlay() override;

	// Runs once every frame
	virtual void Tick(float DeltaTime) override;

private:
	// Get the tank that's controlled by the player
	ATank* GetControlledTank() const;

	// Make the tank move the barrel towards the point
	// where the crosshair intersects the world
	void AimAtCrosshair();
};
