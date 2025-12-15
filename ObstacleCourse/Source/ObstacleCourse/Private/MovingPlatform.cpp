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
	InitialRotation = GetActorRotation();

	SetShouldMove(IsMovingPlatform);
	SetShouldRotate(RotationType != EPlatformRotationType::None);

	UpdateTargetRotation();
}

void AMovingPlatform::OnReachedAMovementEnd(float TargetMovementIncrement)
{
	MovementIncrement = TargetMovementIncrement;
	CurrentMovementWaitDuration = WaitDurationOnMovementEnds;
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
	if(!ShouldRotate || ShouldWaitForRotation(DeltaTime))
	{
		return;
	}
	
	switch(RotationType)
	{
	case EPlatformRotationType::Continuous:	OnContinuousRotation(DeltaTime); break;
	case EPlatformRotationType::ContinuousWithStops: OnContinuousRotationWithStops(DeltaTime); break;
	case EPlatformRotationType::ToTargetAndBack: OnToTargetAndBackRotation(DeltaTime); break;
	default: break;
	}

	SetActorRotation(Rotator);
}

void AMovingPlatform::OnContinuousRotation(const float DeltaTime)
{
	const FVector RotationAmount = RotationOffset * RotationDurationOrSpeed * RotationIncrement * DeltaTime;
	Rotator.Add(RotationAmount.X, RotationAmount.Y, RotationAmount.Z);
}

void AMovingPlatform::OnContinuousRotationWithStops(const float DeltaTime)
{
	OnContinuousRotation(DeltaTime);
    
	if(Rotator.EqualsOrientation(TargetRotation, .01))
	{
		CurrentRotationWaitDuration = WaitDurationOnRotationStops;
		UpdateTargetRotation();
	}
}

void AMovingPlatform::OnToTargetAndBackRotation(const float DeltaTime)
{
	OnContinuousRotation(DeltaTime);
	
	if(Rotator.EqualsOrientation(TargetRotation, .01))
	{
		CurrentRotationWaitDuration = WaitDurationOnRotationStops;
		RotationIncrement *= -1.0f;
		UpdateTargetRotation(RotationIncrement);
	}
}

void AMovingPlatform::UpdateTargetRotation(const float OffsetModification)
{
	TargetRotation.Add(
			RotationOffset.X * OffsetModification,
			RotationOffset.Y * OffsetModification,
			RotationOffset.Z * OffsetModification);
}

bool AMovingPlatform::ShouldWaitForMovement(const float DeltaTime)
{
	CurrentMovementWaitDuration -= DeltaTime;
	return CurrentMovementWaitDuration > 0.0f;
}


bool AMovingPlatform::ShouldWaitForRotation(const float DeltaTime)
{
	CurrentRotationWaitDuration -= DeltaTime;
	return CurrentRotationWaitDuration > 0.0f;
}

void AMovingPlatform::SetShouldMove(const bool bShouldMove)
{
	ShouldMove = bShouldMove;
}

void AMovingPlatform::SetShouldRotate(bool bShouldRotate)
{
	ShouldRotate = bShouldRotate;
}

void AMovingPlatform::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateMovement(DeltaTime);
	UpdateRotation(DeltaTime);
}