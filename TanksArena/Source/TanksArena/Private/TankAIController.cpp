// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

#include "Tank.h"
#include "GameFramework/Pawn.h"
#include "Classes/Engine/World.h"
#include "GameFramework/Actor.h"

void ATankAIController::BeginPlay() {
	// Call parent implementation
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime) {
	// Call parent implementation
	Super::Tick(DeltaTime);

	// Get out if there is no controlled tank
	if (!GetControlledAITank())
		return;

	// Find the controlled tank and with it
	// aim at the player location
	GetControlledAITank()->AimAt(FindPlayerController()->GetTargetLocation());
}

ATank* ATankAIController::GetControlledAITank() const {
	// Return the posessed tank
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::FindPlayerController() const {
	// Return a player controller or null if there is none
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

}