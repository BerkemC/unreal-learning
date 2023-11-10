// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "TimerManager.h"

#include <Kismet/GameplayStatics.h>

void ATower::BeginPlay()
{
	Super::BeginPlay();

	CanShoot = true;

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	GetWorldTimerManager().SetTimer(FireCooldownTimerHandle, this, &ATower::FireIfReady, TowerAttackCooldown, true);
}

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (InFireRange())
	{
		RotateTurret(Tank->GetActorLocation());
	}
}

void ATower::FireIfReady()
{
	if (InFireRange())
	{
		Fire();
	}
}

bool ATower::InFireRange()
{
	return  Tank && FVector::Dist(GetActorLocation(), Tank->GetActorLocation()) <= TowerAttackRange;
}
