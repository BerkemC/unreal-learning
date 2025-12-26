// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BattleBlasterGamerMode.generated.h"

class ATank;

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
	
	UPROPERTY()
	ATank* Tank;

	int32 TowerCount;

	void ActorDied(AActor* DeadActor);
	void OnGameOverTimerTimeout();
};
