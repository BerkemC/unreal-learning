// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

#include "Engine/DamageEvents.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Root Mesh"));
	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	TrailParticles = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Trail Particles"));

	SetRootComponent(RootMesh);
	TrailParticles->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	RootMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

// Called every frame
void AProjectile::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::OnHit(
	UPrimitiveComponent* HitComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	FVector NormalImpulse,
	const FHitResult& Hit)
{
	if(const AActor* ThisOwner = GetOwner(); ThisOwner && OtherActor != ThisOwner && OtherActor != this)
	{
		UGameplayStatics::ApplyDamage(
			OtherActor,
			Damage,
			ThisOwner->GetInstigatorController(),
			this,
			UDamageType::StaticClass());

		if(HitParticles)
		{
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(
				GetWorld(),
				HitParticles,
				GetActorLocation(),
				GetActorRotation());
		}
	}
	
	Destroy();
}

