// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TANKSARENA_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	// Called once at the start
	virtual void BeginPlay() override;

	// Get the tank that's controlled by the player
	ATank* GetControlledTank() const;
};
