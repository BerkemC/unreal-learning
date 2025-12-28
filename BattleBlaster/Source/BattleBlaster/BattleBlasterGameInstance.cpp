// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleBlasterGameInstance.h"

#include "Kismet/GameplayStatics.h"

void UBattleBlasterGameInstance::LoadNextLevel()
{
	if(CurrentLevelIndex < LastLevelIndex)
	{
		ChangeLevel(CurrentLevelIndex + 1);
	}
	else
	{
		RestartGame();
	}
}

void UBattleBlasterGameInstance::RestartLevel()
{
	ChangeLevel(CurrentLevelIndex);
}

void UBattleBlasterGameInstance::RestartGame()
{
	ChangeLevel(1);
}

void UBattleBlasterGameInstance::ChangeLevel(const int32 LevelIndex)
{
	if (LevelIndex < 1 || LevelIndex > LastLevelIndex)
	{
		return;
	}

	CurrentLevelIndex = LevelIndex;
	const FString LevelName = FString::Printf(TEXT("Level_%d"), CurrentLevelIndex);
	UGameplayStatics::OpenLevel(GetWorld(), *LevelName);
}
