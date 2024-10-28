// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"

#include "ShooterCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void AShooterAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

bool AShooterAIController::IsDead() const
{
	AShooterCharacter* ControlledCharacter = Cast<AShooterCharacter>(GetPawn());
	if (ControlledCharacter != nullptr)
	{
		return ControlledCharacter->IsDead();
	}
	return true;
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
