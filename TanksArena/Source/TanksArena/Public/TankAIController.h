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

protected:
	/**
	* Called once at the start
	*/
	virtual void BeginPlay() override;

	/** Called every frame
	* @param Time it took the last frame to complete
	*/
	virtual void Tick(float DeltaTime) override;
};
