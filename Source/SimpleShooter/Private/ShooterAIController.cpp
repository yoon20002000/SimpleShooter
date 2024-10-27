// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"

#include "Kismet/GameplayStatics.h"

void AShooterAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	AActor* PlayerActor = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if(LineOfSightTo(PlayerActor))
	{
		SetFocus(PlayerActor);
		MoveToActor(PlayerActor, AcceptanceRadius);	
	}
	else
	{
		ClearFocus(EAIFocusPriority::Gameplay);
		StopMovement();
	}
}

void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();
}
