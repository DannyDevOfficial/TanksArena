// This code is property of dannydev. All rights reserved.

#include "TankAIController.h"

#include "Tank.h"

#include "TankAimingComponent.h"
#include "GameFramework/Pawn.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"

void ATankAIController::BeginPlay() {
	// Call parent implementation
	Super::BeginPlay();
}

void ATankAIController::SetPawn(APawn* InPawn) {
	// Very important to let the parent set the pawn
	Super::SetPawn(InPawn);

	// Make sure there is a pawn set
	if (InPawn) {
		// Cast the pawn to a Tank
		ATank* possessedTank = Cast<ATank>(InPawn);
		// Get out if there is no possessed tank
		if (!ensure(possessedTank))
			return;

		// Register for the OnDeath event
		possessedTank->OnDeath.AddUniqueDynamic(this,
			&ATankAIController::OnTankDeath);
	}
}

void ATankAIController::Tick(float DeltaTime) {
	// Call parent implementation
	Super::Tick(DeltaTime);

	// Get player target and aiming component
	APawn* playerTarget = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto aimingComp =
		GetPawn()->FindComponentByClass<UTankAimingComponent>();

	// Get out if there is no controlled tank or player
	if (!ensure(playerTarget && aimingComp))
		return;

	// Move ai tank towards player
	MoveToActor(playerTarget, _acceptanceRadius);

	// Aim at the player location
	aimingComp->AimAt(playerTarget->GetTargetLocation());

	// Fire a projectile at the player
	// only if aim is locked
	if (aimingComp->GetFiringState() == EFiringState::Locked)
		aimingComp->Fire();
}

void ATankAIController::OnTankDeath() {
	// Get out if there's no pawn
	if (!GetPawn())
		return;

	// Stop controlling tanks when you're dead!
	GetPawn()->DetachFromControllerPendingDestroy();
}
