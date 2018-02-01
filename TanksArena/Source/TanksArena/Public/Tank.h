// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class UTankAimingComponent;
class UTankBarrel;
class UTankTurret;
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
	/** Aim at the location that was passed in
	* @param Vector used to set the aim
	*/
	void AimAt(FVector hitPosition) const;

	/** Fires projectiles when its bound input it triggered
	*/
	UFUNCTION(BlueprintCallable, Category = "Input")
		void Fire() const;

	/** Setter for the barrel static mesh
	* @param UStaticMeshComponent representing the barrel to set
	*/
	UFUNCTION(BlueprintCallable, Category = "Setup")
		void SetBarrel(UTankBarrel* barrel);

	/** Setter for the turret static mesh
	* @param UStaticMeshComponent representing the turret to set
	*/
	UFUNCTION(BlueprintCallable, Category = "Setup")
		void SetTurret(UTankTurret* turret) const;

private:
	UTankAimingComponent* _tankAimingComponent = nullptr;	// Reference to the tank aiming component
															// needed to delegate tasks to
	
	UTankBarrel* _barrel = nullptr;							// Reference to a barrel static mesh component
	
	UPROPERTY(EditAnywhere, Category = "Firing")
		TSubclassOf<AProjectile> _projectile = nullptr;				// Reference to a projectile that will be spawned

	UPROPERTY(EditAnywhere, Category = "Firing")
		float _launchSpeed = 4000.0f;						// Speed at which to launch the projectiles
};
