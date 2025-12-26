// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

class ATank;

/**
 * 
 */
UCLASS()
class BATTLEBLASTER_API ATower : public ABasePawn
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	float FireRange = 300.0f;
	
	UPROPERTY(EditAnywhere)
	float FireRate = 2.0f;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY()
	ATank* Tank;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void CheckFireCondition();
	bool IsPlayerPawnInRange() const;

	virtual void HandleDestruction() override;
};
