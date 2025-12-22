// Fill out your copyright notice in the Description page of Project Settings.


#include "MoverComponent.h"

#include "EntitySystem/MovieSceneEntitySystemRunner.h"

// Sets default values for this component's properties
UMoverComponent::UMoverComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UMoverComponent::BeginPlay()
{
	Super::BeginPlay();

	MovedActor = GetOwner();

	if(MovedActor)
	{
		StartLocation = MovedActor->GetActorLocation();

		if(ShouldMove)
		{
			MoveToOffsetLocation();
		}
	}
}


// Called every frame
void UMoverComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(!MovedActor)
	{
		return;
	}

	TargetLocation = ShouldMove ? StartLocation + MovementOffset : StartLocation;

	MovedActor->SetActorLocation(
		FMath::VInterpConstantTo(
			MovedActor->GetActorLocation(),
			TargetLocation, 
			DeltaTime,
			MovementOffset.Length() / MovementTime));
}

void UMoverComponent::MoveToStartLocation()
{
	SetTargetLocation(StartLocation);
}

void UMoverComponent::MoveToOffsetLocation()
{
	SetTargetLocation(StartLocation + MovementOffset);
}

void UMoverComponent::SetShouldMove(const bool NewState)
{
	ShouldMove = NewState;
}

void UMoverComponent::SetTargetLocation(const FVector& NewTargetLocation)
{
	TargetLocation = NewTargetLocation;
	ShouldMove = true;
}



