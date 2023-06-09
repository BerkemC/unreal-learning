// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Resource.h"
#include "CollectableResource.generated.h"

/**
 * 
 */
UCLASS()
class TUTORIAL_API ACollectableResource : public AResource
{
	GENERATED_BODY()

public:

	ACollectableResource();

	UFUNCTION(BlueprintCallable)
	void ScaleResourceOnProximity(float DeltaTime);

	void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, Category = "Resource")
	FVector MinScaleSize;

	UPROPERTY(EditAnywhere, Category = "Resource")
	float ScaleSpeed = 2.0f;

	float timeElapsed = 0.0f;
	FVector initialScale;

protected:

	void BeginPlay() override;
};
