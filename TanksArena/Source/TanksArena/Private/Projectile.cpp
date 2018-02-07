// This code is property of dannydev. All rights reserved.

#include "Projectile.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Add a projectile movement component and disable auto activate on it
	_projectileMovComp = 
		CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement Component"));

	_projectileMovComp->bAutoActivate = false;

	// Add a static mesh component for collisions
	// and a particle system component
	_collisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
	_launchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast"));

	// Set default root component and some properties
	SetRootComponent(_collisionMesh);
	_collisionMesh->SetNotifyRigidBodyCollision(true);
	_collisionMesh->SetVisibility(false);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::Launch(float speed) const {
	// Set projectile velocity
	_projectileMovComp->SetVelocityInLocalSpace(FVector::ForwardVector * speed);

	// Activate the projectile movement component
	_projectileMovComp->Activate();
}
