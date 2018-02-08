// This code is property of dannydev. All rights reserved.

#include "Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float ATank::GetHealthPercentage() const {
	return float(_currentHealth) / float(_startingHealth);
}

float ATank::TakeDamage(float DamageAmount,
	struct FDamageEvent const & DamageEvent,
	class AController* EventInstigator,
	AActor* DamageCauser) {
	// Round the damage amount to the nearest integer
	int32 integralDamageAmount = FMath::RoundToInt(DamageAmount);

	// Clamp the damage amount taken
	// between the current health and min health
	float actualDamageToApply =
		FMath::Clamp(integralDamageAmount, int32(0), _currentHealth);

	// Decrease current health
	_currentHealth -= actualDamageToApply;

	// No heatlh left
	if (_currentHealth <= 0)
		// Handle tank's death
		OnDeath.Broadcast();

	return actualDamageToApply;
}
