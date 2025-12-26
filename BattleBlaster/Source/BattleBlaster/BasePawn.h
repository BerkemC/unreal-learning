// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Projectile.h"
#include "BasePawn.generated.h"

class UHealth;
class UCapsuleComponent;
class UStaticMeshComponent;

UCLASS()
class BATTLEBLASTER_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();
	
	UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* CapsuleComponent;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* ProjectileSpawnLocation;

	UPROPERTY(VisibleAnywhere)
	UHealth* HealthComponent;

	UPROPERTY(EditAnywhere)
	float TurretRotationSpeed = 10.0f;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AProjectile> ProjectileClass;
	
	void RotateTurret (const FVector& LookAtTarget) const;

	void Fire();

	virtual void HandleDestruction();
};
