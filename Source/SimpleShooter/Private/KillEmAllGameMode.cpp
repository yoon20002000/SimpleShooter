// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"

#include "EngineUtils.h"
#include "ShooterAIController.h"
#include "ShooterCharacter.h"
#include "ShooterPlayerController.h"

AKillEmAllGameMode::AKillEmAllGameMode()
{
}

void AKillEmAllGameMode::PawnKilled(APawn* PawnKilled)
{
	Super::PawnKilled(PawnKilled);
	if(APlayerController* PlayerController = Cast<APlayerController>( PawnKilled->GetController()); PlayerController !=nullptr)
	{
		EndGame(false);
	}
	
	for(AShooterAIController* Controller : TActorRange<AShooterAIController>(GetWorld()))
	{
		if(Controller != nullptr && Controller->IsDead() == false)
		{
			return;
		}
	}

	EndGame(true);
}

void AKillEmAllGameMode::EndGame(bool bIsPlayerWinner) const
{
	for(APlayerController* Controller : TActorRange<APlayerController>(GetWorld()))
	{
		bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;
		Controller->ClientGameEnded(Controller->GetPawn(), bIsWinner);
	}
}
