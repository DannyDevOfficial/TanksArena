// This code is property of dannydev. All rights reserved.

#pragma once

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

private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float _acceptanceRadius = 3000.0f;	// How far does the AI tank have to be before it stops moving
};
