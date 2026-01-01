// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShooterSamGameMode.h"

#include "ShooterAI.h"
#include "ShooterSamCharacter.h"
#include "Kismet/GameplayStatics.h"

AShooterSamGameMode::AShooterSamGameMode()
{
	// stub
}

void AShooterSamGameMode::BeginPlay()
{
	Super::BeginPlay();

	if(APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0))
	{
		if(AShooterSamCharacter* PlayerCharacter = Cast<AShooterSamCharacter>(PlayerPawn))
		{
			TArray<AActor*> Enemies;
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), AShooterAI::StaticClass(), Enemies);

			for(int32 i = 0; i < Enemies.Num(); i++)
			{
				if(AShooterAI* Shooter = Cast<AShooterAI>(Enemies[i]))
				{
					Shooter->StartBehaviourTree(PlayerCharacter);
				}
			}
		}
	}
}
