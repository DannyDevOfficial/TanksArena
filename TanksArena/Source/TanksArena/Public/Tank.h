// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class UTankAimingComponent;
class UTankBarrel;
class UTankTurret;

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

	/** Setter for the barrel static mesh
	* @param UStaticMeshComponent representing the barrel to set
	*/
	UFUNCTION(BlueprintCallable, Category = "Setup")
		void SetBarrel(UTankBarrel* barrel) const;

	/** Setter for the turret static mesh
	* @param UStaticMeshComponent representing the turret to set
	*/
	UFUNCTION(BlueprintCallable, Category = "Setup")
		void SetTurret(UTankTurret* turret) const;

private:
	UTankAimingComponent* _tankAimingComponent = nullptr;	// Reference to the tank aiming component
															// needed to delegate tasks to

	UPROPERTY(EditAnywhere, Category = "Firing")
		float _launchSpeed = 10000.0f;						// Speed at which to launch the projectiles
};
