// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"

#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "ShooterCharacter.h"

// Sets default values
AGun::AGun()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(RootComp);
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComp);
}

void AGun::PullTrigger()
{
	UGameplayStatics::SpawnEmitterAttached(MuzzleEffect, Mesh,TEXT("MuzzleFlashSocket"));
	if (const APawn* OwnerPawn = Cast<APawn>(GetOwner()); OwnerPawn != nullptr)
	{
		if(AController* OwnerController = OwnerPawn->GetController(); OwnerController != nullptr)
		{
			FVector OutLocation;
			FRotator OutRotation;
			OwnerController->GetPlayerViewPoint(OutLocation, OutRotation);
			DrawDebugCamera(GetWorld(), OutLocation, OutRotation, 90, 2, FColor::Red, true);
		}
	}
	
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
