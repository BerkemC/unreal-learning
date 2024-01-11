// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseProjectile.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"


// Sets default values
ABaseProjectile::ABaseProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = ProjectileMesh;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ProjectileMovement->MaxSpeed = 1300.0f;
	ProjectileMovement->InitialSpeed = 1300.0f;

	TrailParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Trail Particle System"));
	TrailParticleSystem->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABaseProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	ProjectileMesh->OnComponentHit.AddDynamic(this, &ABaseProjectile::OnHit);
}

// Called every frame
void ABaseProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseProjectile::OnHit(
	UPrimitiveComponent* HitComp, 
	AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, 
	FVector NormalImpulse, 
	const FHitResult& Hit)
{
	auto ProjectileOwner = GetOwner();
	if (!ProjectileOwner || !OtherActor || OtherActor == this || OtherActor == ProjectileOwner)
	{
		Destroy();
		return;
	}

	UGameplayStatics::ApplyDamage(
		OtherActor, 
		Damage, 
		ProjectileOwner->GetInstigatorController(),
		this, 
		UDamageType::StaticClass());

	if (HitParticles)
	{
		UGameplayStatics::SpawnEmitterAtLocation(
			this,
			HitParticles,
			GetActorLocation(),
			GetActorRotation());
	}

	Destroy();
}
