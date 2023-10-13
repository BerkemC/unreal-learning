// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"

UTriggerComponent::UTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TArray<AActor*> overlappingActors;
	GetOverlappingActors(overlappingActors);

	for (AActor* actor : overlappingActors)
	{
		auto owner = actor->GetOwner();

		if (!owner)
		{
			continue;
		}

		if (!owner->ActorHasTag(OverlapEventTag))
		{
			continue;
		}

		if (!Mover)
		{
			UE_LOG(LogTemp, Display, TEXT("No Mover!"));
			continue;
		}

		UE_LOG(LogTemp, Display, TEXT("Here"));

		Mover->SetShouldMove(true);
	}
}

void UTriggerComponent::SetMover(UMover* mover)
{
	UE_LOG(LogTemp, Display, TEXT("Setting Mover"));
	if (!mover)
	{
		UE_LOG(LogTemp, Display, TEXT("Mover is null"));
	}
	Mover = mover;
}
