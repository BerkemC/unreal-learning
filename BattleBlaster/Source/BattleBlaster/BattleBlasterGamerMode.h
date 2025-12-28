// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BattleBlasterGamerMode.generated.h"

class ATank;
class UScreenMessage;

/**
 * 
 */
UCLASS()
class BATTLEBLASTER_API ABattleBlasterGamerMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere)
	float GameOverDelay = 3.0f;

	UPROPERTY(EditAnywhere)
	int32 LevelStartDelay = 3.0f;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UScreenMessage> ScreenMessageClass;
	
	UPROPERTY()
	ATank* Tank;

	void ActorDied(AActor* DeadActor);
	void OnGameOverTimerTimeout();
	void OnLevelStartTimerTimeout();

private:
	bool IsVictory = false;

	int32 TowerCount;
	int32 LevelStartSeconds;

	FTimerHandle LevelStartTimer;

	UPROPERTY()
	UScreenMessage* ScreenMessageWidget;
};
