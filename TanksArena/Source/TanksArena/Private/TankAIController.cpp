// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

#include "Tank.h"
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

	// Get controlled tank and player target
	ATank* controlledAItank = Cast<ATank>(GetPawn());
	ATank* playerTarget = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

	// Get out if there is no controlled tank or player
	if (!ensure(controlledAItank && playerTarget))
		return;

	// Move ai tank towards player
	MoveToActor(playerTarget, _acceptanceRadius);

	// Find the controlled tank and with it
	// aim at the player location
	controlledAItank->AimAt(playerTarget->GetTargetLocation());

	// Fire a projectile at the player
	controlledAItank->Fire();
}
