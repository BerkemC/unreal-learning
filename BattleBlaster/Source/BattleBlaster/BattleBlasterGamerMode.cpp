// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleBlasterGamerMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"

void ABattleBlasterGamerMode::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> Towers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATower::StaticClass(), Towers);
	TowerCount = Towers.Num();

	if(APawn* TankPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0))
	{
		Tank = Cast<ATank>(TankPawn);

		for(int32 i = 0; i < TowerCount; i++)
		{
			AActor* TowerActor = Towers[i]; 
			if(!TowerActor)
			{
				continue;
			}
		
			ATower* Tower = Cast<ATower>(TowerActor);
			Tower->Tank = Tank;
		}
	}
}
