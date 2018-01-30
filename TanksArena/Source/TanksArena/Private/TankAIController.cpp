// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

#include "Tank.h"
#include "GameFramework/Pawn.h"
#include "Classes/Engine/World.h"
#include "GameFramework/Actor.h"

void ATankAIController::BeginPlay() {
	// Call parent implementation
	Super::BeginPlay();

	//// Log to console only if there is a valid pointer
	//ATank* posessedAITank = GetControlledAITank();
	//if (posessedAITank) {
	//	UE_LOG(LogTemp, Warning, TEXT("Posessed Tank: %s"), *posessedAITank->GetName());
	//} else {
	//	UE_LOG(LogTemp, Error, TEXT("There is no posessed AI tank!"));
	//}

	// Log to console the found PlayerController
	// or an error message if there is no PlayerController
	ATank* playerController = FindPlayerController();
	if (playerController) {
		UE_LOG(LogTemp, Warning, TEXT("Found PlayerController: %s"),
			*playerController->GetName());
	} else {
		UE_LOG(LogTemp, Error, TEXT("PlayerController not found!"));
	}
}

ATank* ATankAIController::GetControlledAITank() const {
	// Return the posessed tank
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::FindPlayerController() const {
	// Return a player controller or null if there is none
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

}