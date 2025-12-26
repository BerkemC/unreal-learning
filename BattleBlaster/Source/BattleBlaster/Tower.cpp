// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"

#include "Tank.h"

void ATower::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle FireTimerHandle;
	GetWorldTimerManager().SetTimer(FireTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);
}

void ATower::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(IsPlayerPawnInRange())
	{
		RotateTurret(Tank->GetActorLocation());
	}
}

void ATower::CheckFireCondition()
{
	if(!IsPlayerPawnInRange())
	{
		return;		
	}
	
	Fire();
}

bool ATower::IsPlayerPawnInRange() const
{
	return Tank && FVector::Distance(GetActorLocation(), Tank->GetActorLocation()) <= FireRange;
}
