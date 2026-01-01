// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Gun.generated.h"

UCLASS()
class SHOOTERSAM_API AGun : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* GunMeshComponent;

	UPROPERTY(EditAnywhere)
	float MaxRange = 10000.0f;

	UPROPERTY(VisibleAnywhere)
	class UNiagaraComponent* MuzzleFlashParticleSystem;
	
	UPROPERTY(EditAnywhere)
	class UNiagaraSystem* ImpactParticleSystem; 
	
	UPROPERTY(EditAnywhere)
	float Damage = 10.0f; 
	
	// Sets default values for this actor's properties
	AGun();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void PullTrigger();

	UPROPERTY()
	AController* OwnerController;
};
