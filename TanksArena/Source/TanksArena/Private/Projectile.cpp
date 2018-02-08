// This code is property of dannydev. All rights reserved.

#include "Projectile.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Add a projectile movement component and disable auto activate on it
	_projectileMovComp = 
		CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement Component"));

	_projectileMovComp->bAutoActivate = false;

	// Add components
	_collisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
	_launchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast"));
	_impactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Impact Blast"));
	_explosionForce = CreateDefaultSubobject<URadialForceComponent>(FName("Explosion Force"));

	// Set default root component and some properties
	SetRootComponent(_collisionMesh);
	_collisionMesh->SetNotifyRigidBodyCollision(true);
	_collisionMesh->SetVisibility(false);

	// Attach components to root component
	_launchBlast->AttachToComponent(RootComponent,
		FAttachmentTransformRules::KeepRelativeTransform);
	_impactBlast->AttachToComponent(RootComponent,
		FAttachmentTransformRules::KeepRelativeTransform);
	// Don't activate automatically
	_impactBlast->bAutoActivate = false;
	_explosionForce->AttachToComponent(RootComponent,
		FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	// Register delegate for OnHit() events
	_collisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
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

void AProjectile::OnHit(UPrimitiveComponent* HitComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComponent,
	FVector NormalImpulse,
	const FHitResult& Hit) {
	// Deactivate the launch blast
	_launchBlast->Deactivate();
	// Activate the impact blast
	_impactBlast->Activate();

	// Add explosion force
	_explosionForce->FireImpulse();
}
