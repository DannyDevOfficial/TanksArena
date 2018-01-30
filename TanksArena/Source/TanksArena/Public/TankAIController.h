// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class ATank;

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * Controls the tanks used by the AI
 */
UCLASS()
class TANKSARENA_API ATankAIController : public AAIController
{
	GENERATED_BODY()

private:
	// Runs once at the start
	virtual void BeginPlay() override;

private:
	// Gets the tank being controlled by this controller
	ATank* GetControlledAITank() const;

	// Searches the world for a player controller
	ATank* FindPlayerController() const;
};
