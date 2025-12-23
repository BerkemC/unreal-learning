// Fill out your copyright notice in the Description page of Project Settings.


#include "Lock.h"

#include "TriggerComponent.h"

const FName LockTag = "Lock";

// Sets default values
ALock::ALock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if(!ActorHasTag(LockTag))
	{
		Tags.Add(LockTag);
	}
	
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	TriggerComponent = CreateDefaultSubobject<UTriggerComponent>(TEXT("Trigger"));
	ItemMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Item Mesh"));
	
	SetRootComponent(Root);
	TriggerComponent->SetupAttachment(Root);
	ItemMeshComponent->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void ALock::BeginPlay()
{
	Super::BeginPlay();
	SetIsKeyPlaced(false);
}

// Called every frame
void ALock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALock::SetIsKeyPlaced(const bool bIsKeyPlaced)
{
	IsKeyPlaced = bIsKeyPlaced;

	if(ItemMeshComponent)
	{
		ItemMeshComponent->SetVisibility(IsKeyPlaced);
	}

	if(TriggerComponent)
	{
		TriggerComponent->SetTrigger(IsKeyPlaced);
	}
}

bool ALock::GetIsKeyPlaced() const
{
	return IsKeyPlaced;
}

FName ALock::Collect()
{
	SetIsKeyPlaced(false);
	return KeyItemName;
}

