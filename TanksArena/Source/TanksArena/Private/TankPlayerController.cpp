// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "GameFramework/Pawn.h"

void ATankPlayerController::BeginPlay() {
	// Execute what's in the parent class
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("BeginPlay called"));

	// Log to console only if there is a valid pointer
	ATank* posessedTank = GetControlledTank();
	if (posessedTank) {
		UE_LOG(LogTemp, Warning, TEXT("Posessed Tank: %s"), *posessedTank->GetName());
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("There is no posessed tank!"));
	}
}


ATank* ATankPlayerController::GetControlledTank() const {
	// Cast the pawn component to a tank component since we know
	// that's what it is
	return Cast<ATank>(GetPawn());
}

