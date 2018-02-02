// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

/**
 * Gives control over the movement of the tank
 */
UCLASS()
class TANKSARENA_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

public:
	/** Sets up the tank to move forward and backwards
	* @param How far forward or backwards the tank will move
	*/
	UFUNCTION(BlueprintCallable, Category = "Input")
		void IntendMoveForward(float theThrow) const;
};
