// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPlatform.generated.h"

UENUM(BlueprintType)
enum EPlatformRotationType : uint8
{
	None UMETA(DisplayName = "None"),
	Continuous UMETA(DisplayName = "Continous Rotation"),
	ToTargetAndBack UMETA(DisplayName = "To Target And Back Rotation"),
	ContinuousWithStops UMETA(DisplayName = "Continuous Rotation With Stops"),
};

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

	UPROPERTY(EditAnywhere)
	float WaitDurationOnMovementEnds = 0.0f;

	UPROPERTY(EditAnywhere)
	TEnumAsByte<EPlatformRotationType> RotationType = EPlatformRotationType::None;
	
	UPROPERTY(EditAnywhere)
	FRotator RotationOffset = FRotator(0, 0, 0);

	UPROPERTY(EditAnywhere)
	float RotationDurationOrSpeed = 0.0f;
	
	UPROPERTY(EditAnywhere)
	float WaitDurationOnRotationStops = 0.0f;
	
	// Sets default values for this actor's properties
	AMovingPlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void OnReachedAMovementEnd(float TargetMovementIncrement);
	void UpdateMovement(float DeltaTime);
	bool ShouldWaitForMovement(float DeltaTime);

	void UpdateRotation(float DeltaTime);
	void OnContinuousRotation(float DeltaTime);
	void OnContinuousRotationWithStops(float DeltaTime);
	void OnToTargetAndBackRotation(float DeltaTime);
	void UpdateTargetRotation(float OffsetModification = 1.0f);

	bool ShouldWaitForRotation(float DeltaTime);
	
private:
	FVector InitialLocation = FVector(0, 0, 0);
	FRotator TargetRotation = FRotator::ZeroRotator;

	float CurrentMovementTimer = 0.0f;
	float MovementIncrement = 1.0f;
	float CurrentMovementWaitDuration = 0.0f;
	float CurrentRotationWaitDuration = 0.0f;
	float RotationIncrement = 1.0f;

	bool ShouldMove = false;
	bool ShouldRotate = false;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetShouldMove(bool bShouldMove);
	void SetShouldRotate(bool bShouldRotate);
};