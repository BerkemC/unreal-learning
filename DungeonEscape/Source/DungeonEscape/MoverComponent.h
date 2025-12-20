// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MoverComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUNGEONESCAPE_API UMoverComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	FVector MovementOffset = FVector::ZeroVector;

	UPROPERTY(EditAnywhere)
	float MovementTime = 5.0f;

	UPROPERTY(EditAnywhere)
	bool ShouldMove = false;
	
	// Sets default values for this component's properties
	UMoverComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(
		float DeltaTime,
		ELevelTick TickType,
		FActorComponentTickFunction* ThisTickFunction) override;

	void MoveToStartLocation();
	void MoveToOffsetLocation();

private:
	FVector StartLocation = FVector::ZeroVector;
	FVector TargetLocation = FVector::ZeroVector;

	AActor* MovedActor = nullptr;

	void SetTargetLocation(const FVector& NewTargetLocation);
};
