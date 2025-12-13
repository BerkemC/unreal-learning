// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPlatform.generated.h"

UCLASS()
class OBSTACLECOURSE_API AMovingPlatform : public AActor
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere)
	bool IsMovingPlatform = false;
	
	UPROPERTY(EditAnywhere)
	FVector TargetMovementOffset = FVector(0, 0, 0);

	UPROPERTY(EditAnywhere)
	float MoveDuration = 5.0f;
	
	// Sets default values for this actor's properties
	AMovingPlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void UpdateMovement(float DeltaTime);
	
private:
	FVector InitialLocation = FVector(0, 0, 0);

	float CurrentMovementTimer = 0.0f;
	float MovementIncrement = 1.0f;

	bool ShouldMove = false;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetShouldMove(bool bShouldMove);
};
