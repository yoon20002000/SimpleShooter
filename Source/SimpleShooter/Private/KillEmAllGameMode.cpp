// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"

AKillEmAllGameMode::AKillEmAllGameMode()
{
}

void AKillEmAllGameMode::PawnKilled(APawn* PawnKilled)
{
	Super::PawnKilled(PawnKilled);
	UE_LOG(LogTemp, Log, TEXT("Pawn was dead : %s"), *PawnKilled->GetName());
}
