// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere)
	float TowerAttackRange = 2000.0f;

	UPROPERTY(EditAnywhere)
	float TowerAttackCooldown = 5.0f;

private:
	class ATank* Tank;

	bool CanShoot = true;
	FTimerHandle FireCooldownTimerHandle;

	void FireIfReady();
	bool InFireRange();
};
