// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class UTankBarrel;
class AProjectile;

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
	/** Fires projectiles when its bound input it triggered
	*/
	UFUNCTION(BlueprintCallable, Category = "Input")
		void Fire();														// needed to delegate tasks to

private:	
	UTankBarrel* _barrel = nullptr;								// Reference to a barrel static mesh component
	
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		TSubclassOf<AProjectile> _projectile = nullptr;			// Reference to a projectile that will be spawned

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float _launchSpeed = 4000.0f;							// Speed at which to launch the projectiles

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		double _reloadTimeSecs = 3.0f;							// Time it takes for the barrel to reload and be able
																// to shoot again

	double _lastTimeReloadedSecs = 0.0f;						// Last time barrel reloaded
};
