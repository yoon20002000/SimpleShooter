// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"

#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "ShooterCharacter.h"
#include "Engine/DamageEvents.h"

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
		if (AController* OwnerController = OwnerPawn->GetController(); OwnerController != nullptr)
		{
			FVector Start;
			FRotator Rotation;
			OwnerController->GetPlayerViewPoint(Start, Rotation);

			FVector End = Start + Rotation.Vector() * MaxRange;

			FHitResult Hit;
			FCollisionQueryParams Params;
			Params.AddIgnoredActor(this);
			Params.AddIgnoredActor(GetOwner());
			if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_GameTraceChannel1,Params))
			{
				FVector ShotDirection = -Rotation.Vector();
				FVector HitLocation = Hit.Location;
				
				if (HitEffect != nullptr)
				{
					UGameplayStatics::SpawnEmitterAtLocation(this, HitEffect, HitLocation,ShotDirection.Rotation());
					
					if (AActor* HitActor = Hit.GetActor(); HitActor != nullptr)
					{
						FPointDamageEvent DamageEvent(Damage, Hit, ShotDirection, nullptr);
						HitActor->TakeDamage(Damage, DamageEvent, OwnerController, this);	
					}
				}
			}
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