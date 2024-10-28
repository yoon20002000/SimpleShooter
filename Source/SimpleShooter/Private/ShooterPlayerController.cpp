// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"


void AShooterPlayerController::ClientGameEnded_Implementation(class AActor* EndGameFocus, bool bIsWinner)
{
	Super::ClientGameEnded_Implementation(EndGameFocus, bIsWinner);
	GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel,RestartDelay);
}
