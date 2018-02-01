// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class UTankBarrel;
class UTankTurret;

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"


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
	/** Takes care of aiming at a given position in the world.
	* @param Vector containing the world location to aim at
	* @param The speed at which to launch a projectile
	*/
	void AimAt(FVector hitWorldLocation, float launchSpeed) const;

	/** Setter for the barrel static mesh
	* @param UStaticMeshComponent representing the barrel to set
	*/
	void SetBarrel(UTankBarrel* barrel);

	/** Setter for the turret static mesh
	* @param UStaticMeshComponent representing the turret to set
	*/
	void SetTurret(UTankTurret* turret);

private:
	/** Calculates barrel rotation and moves it and the turret based on that
	* @param Suggested direction at which to aim
	*/
	void MoveBarrelAndTurret(FVector aimDirection) const;

private:
	UTankBarrel* _barrel = nullptr;					// Reference to the barrel static mesh
	UTankTurret* _turret = nullptr;					// Reference to the turret static mesh

private:
	const FName PROJECTILE_SPAWN_SOCKET = "Projectile Spawn";	// name that was given to the socket where the projectiles will spawn from
};