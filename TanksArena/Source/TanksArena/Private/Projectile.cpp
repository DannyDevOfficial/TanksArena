// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"

#include "GameFramework/ProjectileMovementComponent.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Add a projectile movement component and disable auto activate on it
	_projectileMovComp = 
		CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement Component"));

	_projectileMovComp->bAutoActivate = false;
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
