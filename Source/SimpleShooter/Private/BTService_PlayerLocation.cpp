// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerLocation.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UBTService_PlayerLocation::UBTService_PlayerLocation()
{
	NodeName = "Update Player Location";
}

void UBTService_PlayerLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	if (const AActor* PlayerActor = UGameplayStatics::GetPlayerPawn(GetWorld(), 0); PlayerActor != nullptr)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(),
		                                                     PlayerActor->GetActorLocation());
	}
}
