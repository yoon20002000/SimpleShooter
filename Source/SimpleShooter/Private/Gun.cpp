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
	FHitResult Hit;
	FVector ShotDirection;
	if (GunTrace(Hit, ShotDirection))
	{
		if (HitEffect != nullptr)
		{
			UGameplayStatics::SpawnEmitterAtLocation(this, HitEffect, Hit.Location, ShotDirection.Rotation());

			if (AActor* HitActor = Hit.GetActor(); HitActor != nullptr)
			{
				FPointDamageEvent DamageEvent(Damage, Hit, ShotDirection, nullptr);
				HitActor->TakeDamage(Damage, DamageEvent, GetOwnerController(), this);
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

bool AGun::GunTrace(FHitResult& OutHit, FVector& OutShotDirection) const
{
	const AController* OwnerController = GetOwnerController();

	if (OwnerController == nullptr)
	{
		return false;
	}
	FVector Start;
	FRotator Rotation;
	OwnerController->GetPlayerViewPoint(Start, Rotation);

	FVector End = Start + Rotation.Vector() * MaxRange;
	OutShotDirection = -Rotation.Vector();
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());
	return GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_GameTraceChannel1, Params);
}

AController* AGun::GetOwnerController() const
{
	const APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr)
	{
		return nullptr;
	}
	AController* OwnerController = OwnerPawn->GetController();

	return OwnerController;
}
