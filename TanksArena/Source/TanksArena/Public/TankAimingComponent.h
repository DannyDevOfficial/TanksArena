// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class UTankBarrel;
class UTankTurret;

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

	/** Takes care of aiming at a given position in the world.
	* @param Vector containing the world location to aim at
	*/
	void AimAt(FVector hitWorldLocation) const;

private:
	/** Calculates barrel rotation and moves it and the turret based on that
	* @param Suggested direction at which to aim
	*/
	void MoveBarrelAndTurret(FVector aimDirection) const;

public:
	const static FName PROJECTILE_SPAWN_SOCKET;					// name that was given to the socket where the projectiles will spawn from

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
		EFiringState _firingState = EFiringState::Reloading;	// current state the tank is in

private:
	UTankBarrel* _barrel = nullptr;								// Reference to the barrel static mesh
	UTankTurret* _turret = nullptr;								// Reference to the turret static mesh


	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float _launchSpeed = 4000.0f;
};
