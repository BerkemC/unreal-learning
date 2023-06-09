// Fill out your copyright notice in the Description page of Project Settings.


#include "CollectableResource.h"
#include "Engine/Engine.h"
#include "Logging/LogMacros.h"

ACollectableResource::ACollectableResource() : AResource()
{
}

void ACollectableResource::ScaleResourceOnProximity(float DeltaTime)
{

	auto distance = GetDistanceTo(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto shouldReset = distance >= MaxPlayerProximityForInteraction;
	
	if (shouldReset)
	{
		timeElapsed = 1.0f;
	}
	else
	{
		timeElapsed += DeltaTime;
	}

	auto newScale
		= FMath::Lerp(
			MinScaleSize,
			initialScale,
			shouldReset ? 1.0f : (FMath::Sin(timeElapsed * ScaleSpeed) + 1) / 2.0f);

	SetActorRelativeScale3D(newScale);
}

void ACollectableResource::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ScaleResourceOnProximity(DeltaTime);
}

void ACollectableResource::BeginPlay()
{
	Super::BeginPlay();

	initialScale = GetActorRelativeScale3D();
}
