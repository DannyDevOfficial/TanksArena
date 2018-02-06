// This code is property of dannydev. All rights reserved.

#pragma once

class UTankBarrel;
class UTankTurret;
class AProjectile;

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

/*
* Possible states a tank can be in when aiming
*/
UENUM()
enum class EFiringState : uint8 {
	Reloading,
	Aiming,
	Locked
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANKSARENA_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	/** Initializes the aiming component
	* @param tank turret to set
	* @param tank barrel to set
	*/
	UFUNCTION(BlueprintCallable, Category = "Setup")
		void Initialize(UTankTurret* tankTurret,
			UTankBarrel* tankBarrel);

	/** Fires projectiles when its bound input it triggered
	*/
	UFUNCTION(BlueprintCallable, Category = "Input")
		void Fire();

	/** Takes care of aiming at a given position in the world.
	* @param Vector containing the world location to aim at
	*/
	void AimAt(FVector hitWorldLocation);

private:
	/** Calculates barrel rotation and moves it and the turret based on that
	*/
	void MoveBarrelAndTurret() const;

	/** Checks if the barrel is currently moving
	* @return Whether or not the barrel is moving
	*/
	bool IsBarrelMoving() const;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
		EFiringState _firingState = EFiringState::Reloading;	// current state the tank is in

private:
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		TSubclassOf<AProjectile> _projectile = nullptr;			// Reference to a projectile that will be spawned

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float _launchSpeed = 4000.0f;							// Speed at which to launch the projectiles

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		double _reloadTimeSecs = 3.0f;							// Time it takes for the barrel to reload and be able
																// to shoot again
	double _lastTimeReloadedSecs = 0.0f;						// Last time barrel reloaded

	UTankBarrel* _barrel = nullptr;								// Reference to the barrel static mesh
	UTankTurret* _turret = nullptr;								// Reference to the turret static mesh

	FVector _aimDirection = FVector(0.0f);						// Direction in which the tank should be aiming

private:
	const static FName PROJECTILE_SPAWN_SOCKET;					// name that was given to the socket where the projectiles will spawn from
};
