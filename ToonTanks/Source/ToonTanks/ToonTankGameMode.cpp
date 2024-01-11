// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTankGameMode.h"
#include "ToonTankPlayerController.h"
#include "Tank.h"
#include "Tower.h"
#include "Kismet/GameplayStatics.h"

void AToonTankGameMode::ActorDied(AActor* Actor)
{
	if (!Actor)
	{
		return;
	}

	if (Actor == Tank)
	{
		Tank->HandleDestruction();

		if (ToonTankPlayerController)
		{
			ToonTankPlayerController->SetPlayerEnabledState(false);
		}
	}
	else if (auto Tower = Cast<ATower>(Actor))
	{
		Tower->HandleDestruction();
	}
}

void AToonTankGameMode::BeginPlay()
{
	Super::BeginPlay();

	HandleGameStart();
}

void AToonTankGameMode::HandleGameStart()
{
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	ToonTankPlayerController = Cast<AToonTankPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	if (ToonTankPlayerController)
	{
		ToonTankPlayerController->SetPlayerEnabledState(false);

		FTimerHandle PlayerEnableTimerHandle;
		FTimerDelegate TimerDelegate 
			= FTimerDelegate::CreateUObject(
				ToonTankPlayerController, 
				&AToonTankPlayerController::SetPlayerEnabledState, 
				true);

		GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle, TimerDelegate, StartDelay, false);
	}
}
