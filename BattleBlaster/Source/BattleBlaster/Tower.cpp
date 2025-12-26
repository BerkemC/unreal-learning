// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"

#include "Tank.h"

ATower::ATower() : ABasePawn()
{
}

void ATower::BeginPlay()
{
	Super::BeginPlay();
}

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(Tank && FVector::Distance(GetActorLocation(), Tank->GetActorLocation()) <= FireRange)
	{
		RotateTurret(Tank->GetActorLocation());
	}
}
