// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"

#include "Health.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Component"));
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	ProjectileSpawnLocation = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Location"));
	HealthComponent = CreateDefaultSubobject<UHealth>(TEXT("Health Component"));
	
	SetRootComponent(CapsuleComponent);
	BaseMesh->SetupAttachment(CapsuleComponent);
	TurretMesh->SetupAttachment(BaseMesh);
	ProjectileSpawnLocation->SetupAttachment(TurretMesh);
}

void ABasePawn::RotateTurret(const FVector& LookAtTarget) const
{
	const FVector TurretMeshLocationWS = TurretMesh->GetComponentLocation();
	const FVector FromTurretToImpact = LookAtTarget - TurretMeshLocationWS;
	const FRotator LookAtRotation = FRotator(0.0f, FromTurretToImpact.Rotation().Yaw, 0.0f);

	TurretMesh->SetWorldRotation(
		FMath::RInterpTo(
		TurretMesh->GetComponentRotation(),
		LookAtRotation,
		GetWorld()->GetDeltaSeconds(),
		TurretRotationSpeed));
}

void ABasePawn::Fire()
{
	const FVector SpawnLocation = ProjectileSpawnLocation->GetComponentLocation();
	const FRotator SpawnRotation = ProjectileSpawnLocation->GetComponentRotation();

	if(AProjectile* NewProjectile
			= GetWorld()->SpawnActor<AProjectile>(ProjectileClass, SpawnLocation, SpawnRotation))
	{
		NewProjectile->SetOwner(this);
	}
}

void ABasePawn::HandleDestruction()
{
	if(DeathParticle)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			GetWorld(),
			DeathParticle,
			GetActorLocation(),
			GetActorRotation());
	}
}
