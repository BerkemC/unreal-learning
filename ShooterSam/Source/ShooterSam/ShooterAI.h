// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "ShooterAI.generated.h"

class AShooterSamCharacter;
/**
 * 
 */
UCLASS()
class SHOOTERSAM_API AShooterAI : public AAIController
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
	UBehaviorTree* BehaviorTree;

	virtual void BeginPlay() override;

public:
	UPROPERTY()
	AShooterSamCharacter* Player;

	UPROPERTY()
	AShooterSamCharacter* SelfCharacter;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void StartBehaviourTree(AShooterSamCharacter* PlayerCharacter);
};
