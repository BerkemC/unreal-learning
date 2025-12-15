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
	SetShouldRotate(RotationType != EPlatformRotationType::None);
}

void AMovingPlatform::OnReachedAMovementEnd(float TargetMovementIncrement)
{
	MovementIncrement = TargetMovementIncrement;
	CurrentMovementWaitDuration = WaitDurationOnMovementEnds;
}

bool AMovingPlatform::ShouldWaitForMovement(const float DeltaTime)
{
	CurrentMovementWaitDuration -= DeltaTime;
	return CurrentMovementWaitDuration > 0.0f;
}

void AMovingPlatform::UpdateMovement(const float DeltaTime)
{
	if(!ShouldMove || !IsMovingPlatform || ShouldWaitForMovement(DeltaTime))
	{
		return;
	}

	CurrentMovementTimer += DeltaTime * MovementIncrement;

	if(CurrentMovementTimer > MoveDuration)
	{
		OnReachedAMovementEnd(-1.0f);
	}
	else if(CurrentMovementTimer < 0.0f)
	{
		OnReachedAMovementEnd(1.0f);
	}
	
	const float CurrentRatio = CurrentMovementTimer / MoveDuration;
	const FVector TargetLocation
			= FMath::Lerp(InitialLocation, InitialLocation + TargetMovementOffset, CurrentRatio);

	SetActorLocation(TargetLocation, true);
}

void AMovingPlatform::UpdateRotation(const float DeltaTime)
{
	if(!ShouldRotate)
	{
		return;
	}
	
	switch(RotationType)
	{
	case EPlatformRotationType::Continuous:	OnContinuousRotation(DeltaTime); break;
	default: break;
	}

	SetActorRotation(Rotator);
}

void AMovingPlatform::OnContinuousRotation(const float DeltaTime)
{
	const FVector RotationAmount = RotationOffset * RotationDurationOrSpeed * DeltaTime;
	Rotator.Add(RotationAmount.X, RotationAmount.Y, RotationAmount.Z);
}

void AMovingPlatform::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateMovement(DeltaTime);
	UpdateRotation(DeltaTime);
}

void AMovingPlatform::SetShouldMove(const bool bShouldMove)
{
	ShouldMove = bShouldMove;
}

void AMovingPlatform::SetShouldRotate(bool bShouldRotate)
{
	ShouldRotate = bShouldRotate;
}

