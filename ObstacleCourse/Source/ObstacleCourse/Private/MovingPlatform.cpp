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
	
	InitialLocation = GetActorLocation();

	SetShouldMove(IsMovingPlatform);
}

void AMovingPlatform::UpdateMovement(const float DeltaTime)
{
	if(!ShouldMove || !IsMovingPlatform)
	{
		return;
	}

	CurrentMovementTimer += DeltaTime * MovementIncrement;

	if(CurrentMovementTimer > MoveDuration)
	{
		MovementIncrement = -1.0f;
	}
	else if(CurrentMovementTimer < 0.0f)
	{
		MovementIncrement = 1.0f;
	}
	
	const float CurrentRatio = CurrentMovementTimer / MoveDuration;
	const FVector TargetLocation
			= FMath::Lerp(InitialLocation, InitialLocation + TargetMovementOffset, CurrentRatio);

	SetActorLocation(TargetLocation);
}

// Called every frame
void AMovingPlatform::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateMovement(DeltaTime);
}

void AMovingPlatform::SetShouldMove(const bool bShouldMove)
{
	ShouldMove = bShouldMove;
}

