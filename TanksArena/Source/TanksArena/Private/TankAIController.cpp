// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

#include "TankAimingComponent.h"
#include "GameFramework/Pawn.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"

void ATankAIController::BeginPlay() {
	// Call parent implementation
	Super::BeginPlay();
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

	// TODO Refactor Fire() function, put it in the aiming component
	// Fire a projectile at the player
	//aimingComp->Fire();
}
