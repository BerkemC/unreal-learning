// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	
	initialPosition = GetActorLocation();
	toTarget = TargetPosition - GetActorLocation();
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (currentStopWaitTime > 0.0f)
	{
		currentStopWaitTime -= DeltaTime;
		return;
	}

	float ratio = currentMovementTime / MovementTime;

	if (ratio >= 1.0f)
	{
		isGoingForward = false;
		currentStopWaitTime = StopWaitTime;
	}
	else if (ratio <= 0.0f)
	{
		isGoingForward = true;
		currentStopWaitTime = StopWaitTime;
	}

	currentMovementTime += (isGoingForward ? DeltaTime : - DeltaTime);

	FVector nextLocation = initialPosition + (toTarget * ratio);
	SetActorLocation(nextLocation);
}

