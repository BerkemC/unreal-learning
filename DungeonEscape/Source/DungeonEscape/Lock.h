// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Lock.generated.h"

class UTriggerComponent;
class UStaticMeshComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DUNGEONESCAPE_API ALock : public AActor
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere)
	FName KeyItemName;
	
	// Sets default values for this actor's properties
	ALock();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	UTriggerComponent* TriggerComponent;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* ItemMeshComponent;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetIsKeyPlaced(bool bIsKeyPlaced);
	bool GetIsKeyPlaced() const;

	FName Collect();

private:

	UPROPERTY(VisibleAnywhere)
	bool IsKeyPlaced = false;
};
