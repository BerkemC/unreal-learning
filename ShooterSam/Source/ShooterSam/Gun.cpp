// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"

#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	GunMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Gun Mesh"));
	MuzzleFlashParticleSystem = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Muzzle Flash Particle System"));

	SetRootComponent(Root);
	GunMeshComponent->SetupAttachment(Root);
	MuzzleFlashParticleSystem->SetupAttachment(GunMeshComponent);
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();

	if(MuzzleFlashParticleSystem)
	{
		MuzzleFlashParticleSystem->Deactivate();
	}
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGun::PullTrigger()
{
	if(!OwnerController)
	{
		return;
	}

	if(MuzzleFlashParticleSystem)
	{
		MuzzleFlashParticleSystem->Activate(true);
	}
	
	FVector Location;
	FRotator Rotation;
	OwnerController->GetPlayerViewPoint(Location, Rotation);

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());
	
	FHitResult Hit;
	if(GetWorld()->LineTraceSingleByChannel(
		Hit,
		Location,
		Location + Rotation.Vector() * MaxRange,
		ECC_GameTraceChannel2,
		Params))
	{
		if(ImpactParticleSystem)
		{
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(
				this,
				ImpactParticleSystem,
				Hit.ImpactPoint,
				Hit.ImpactNormal.Rotation());
		}
	}
}

