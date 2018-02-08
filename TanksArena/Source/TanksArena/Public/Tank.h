// This code is property of dannydev. All rights reserved.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

UCLASS()
class TANKSARENA_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	/* Get the health mapped to 0 to 1
	* @return the current health in percentage
	*/
	UFUNCTION(BlueprintPure, Category = "Health")
		float GetHealthPercentage() const;

protected:
	virtual float TakeDamage(float DamageAmount,
		struct FDamageEvent const & DamageEvent,
		class AController* EventInstigator,
		AActor* DamageCauser) override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		int32 _startingHealth = 100;		// How much health the tank starts with

private:
	int32 _currentHealth = _startingHealth;	// Amount of health this tank has left
};
