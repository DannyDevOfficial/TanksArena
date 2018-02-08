// This code is property of dannydev. All rights reserved.

#pragma once

class UProjectileMovementComponent;
class UParticleSystemComponent;
class UStaticMeshComponent;
class URadialForceComponent;

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TANKSARENA_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	/** Launches the projectile forward at the given speed
	* @param Speed at which to launch the projectile
	*/
	void Launch(float speed) const;

private:
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComponent,
			FVector NormalImpulse,
			const FHitResult& Hit);

	/* Do this when a projectile hits something
	*/
	void ProjectileHitSomething();

private:
	UProjectileMovementComponent* _projectileMovComp = nullptr;	// reference to a projectile movement component

	UPROPERTY(VisibleAnywhere, Category = "Projectile Component")
		UStaticMeshComponent* _collisionMesh = nullptr;				// reference to a static mesh component used for collisions

	UPROPERTY(VisibleAnywhere, Category = "Projectile Component")
		UParticleSystemComponent* _launchBlast = nullptr;			// reference to a particle system component used for the shot blast

	UPROPERTY(VisibleAnywhere, Category = "Projectile Component")
		UParticleSystemComponent* _impactBlast = nullptr;			// reference to a particle system component used for the impact blast

	UPROPERTY(VisibleAnywhere, Category = "Projectile Component")
		URadialForceComponent* _explosionForce = nullptr;			// reference to a radial force used to simulate explosion force

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float _destructionTimerSecs = 0.5f;							// How long before the projectile gets destroyed

};
