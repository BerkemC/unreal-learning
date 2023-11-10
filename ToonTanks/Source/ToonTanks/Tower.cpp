// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"

#include <Kismet/GameplayStatics.h>

void ATower::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
}

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Tank &&
		FVector::Dist(GetActorLocation(), Tank->GetActorLocation()) <= TowerAttackRange)
	{
		RotateTurret(Tank->GetActorLocation());
	}
}
