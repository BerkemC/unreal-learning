// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPlatform.generated.h"

UCLASS()
class UNREALLEARNINGKIT_API AMovingPlatform : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	FVector TargetPosition;

	UPROPERTY(EditAnywhere)
	float MovementTime;

	UPROPERTY(EditAnywhere)
	float StopWaitTime = 5.0f;

public:	
	// Sets default values for this actor's properties
	AMovingPlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	float currentMovementTime = 0;
	float currentStopWaitTime;
	bool isGoingForward = false;
	
	FVector initialPosition;
	FVector toTarget;
};
