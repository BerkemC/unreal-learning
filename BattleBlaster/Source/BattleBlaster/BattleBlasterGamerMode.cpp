// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleBlasterGamerMode.h"

#include "BattleBlasterGameInstance.h"
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

void ABattleBlasterGamerMode::ActorDied(AActor* DeadActor)
{
	if(!DeadActor)
	{
		return;
	}

	bool IsGameOver = false;
	
	if(DeadActor == Tank)
	{
		Tank->HandleDestruction();
		IsGameOver = true;
	}
	else
	{
		if(ATower* DeadTower = Cast<ATower>(DeadActor))
		{
			DeadTower->HandleDestruction();
			IsVictory = --TowerCount <= 0;
			IsGameOver |= IsVictory;
		}
	}

	if(IsGameOver)
	{
		if(IsVictory)
		{
			
		}
		else
		{
		
		}
		
		FTimerHandle GameOverTimer;
		GetWorldTimerManager().SetTimer(
			GameOverTimer,
			this,
			&ABattleBlasterGamerMode::OnGameOverTimerTimeout,
			GameOverDelay, 
			false);
	}
}

void ABattleBlasterGamerMode::OnGameOverTimerTimeout()
{
	if(UGameInstance* Instance = GetGameInstance())
	{
		if(UBattleBlasterGameInstance* GameInstance = Cast<UBattleBlasterGameInstance>(Instance))
		{
			if(IsVictory)
			{
				GameInstance->LoadNextLevel();
			}
			else
			{
				GameInstance->RestartLevel();
			}
		}
	}
}
