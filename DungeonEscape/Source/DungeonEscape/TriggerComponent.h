// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "TriggerComponent.generated.h"

class UMoverComponent;

/**
 * 
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DUNGEONESCAPE_API UTriggerComponent : public UBoxComponent
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	AActor* MoverActor;

	UPROPERTY(EditAnywhere)
	bool IsPressurePlate = false;

	UPROPERTY(EditAnywhere)
	FName RequiredPressurePlateTag = "PressurePlateUser";
	
	UTriggerComponent();
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(
		float DeltaTime,
		ELevelTick TickType,
		FActorComponentTickFunction* ThisTickFunction) override;

	void SetTrigger(bool State);
	
private:
	UPROPERTY()
	UMoverComponent* MoverComponent = nullptr;

	int32 OverlappingActorCount = 0;
	
	void SetMoverStateForPressurePlate(bool TargetState, const AActor* OtherActor);
	
	UFUNCTION()
	void OnOverlapBegin(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);
	
	UFUNCTION()
	void OnOverlapEnd(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);
};
