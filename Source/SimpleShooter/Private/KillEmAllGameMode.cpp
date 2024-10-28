// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"

#include "ShooterPlayerController.h"

AKillEmAllGameMode::AKillEmAllGameMode()
{
}

void AKillEmAllGameMode::PawnKilled(APawn* PawnKilled)
{
	Super::PawnKilled(PawnKilled);
	if(APlayerController* PlayerController = Cast<APlayerController>( PawnKilled->GetController()); PlayerController !=nullptr)
	{
		PlayerController->ClientGameEnded(nullptr,false);
	}
	
	UE_LOG(LogTemp, Log, TEXT("Pawn was dead : %s"), *PawnKilled->GetName());
}
