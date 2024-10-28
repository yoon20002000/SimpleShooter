// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void AShooterAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	AActor* PlayerActor = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if(LineOfSightTo(PlayerActor))
	{
		const FVector PlayerLocation = PlayerActor->GetActorLocation();
		GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"),PlayerLocation);
		GetBlackboardComponent()->SetValueAsVector(TEXT("LastKnownPlayerLocation"),PlayerLocation);
	}
	else
	{
		GetBlackboardComponent()->ClearValue(TEXT("PlayerLocation"));
	}
}

void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();
	if(AIBehavior != nullptr)
	{
		RunBehaviorTree(AIBehavior);
		
		if(AActor* PlayerActor = UGameplayStatics::GetPlayerPawn(GetWorld(), 0); PlayerActor != nullptr)
		{
			GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"),PlayerActor->GetActorLocation());
			GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"),GetPawn()->GetActorLocation());
		}
	}
}
