// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"

#include "Kismet/GameplayStatics.h"

void AShooterAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	AActor* PlayerActor = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	MoveToActor(PlayerActor, 200);
}

void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();
	AActor* PlayerActor = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	SetFocus(PlayerActor);
	MoveToActor(PlayerActor);
}
