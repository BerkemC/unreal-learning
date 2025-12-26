// Fill out your copyright notice in the Description page of Project Settings.


#include "Health.h"

#include "BattleBlasterGamerMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UHealth::UHealth()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	ResetHealth();
}


// Called when the game starts
void UHealth::BeginPlay()
{
	Super::BeginPlay();

	ResetHealth();

	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealth::UHealth::OnDamageTaken);

	if(AGameModeBase* GameModeBase = UGameplayStatics::GetGameMode(GetWorld()))
	{
		GameMode = Cast<ABattleBlasterGamerMode>(GameModeBase);
	}
}


// Called every frame
void UHealth::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealth::ResetHealth()
{
	CurrentHealth = MaxHealth;
}

void UHealth::ApplyDamage(const float Damage)
{
	CurrentHealth = FMath::Clamp(CurrentHealth - Damage, 0, MaxHealth);
}

bool UHealth::IsDead() const
{
	return CurrentHealth < 0.0f || FMath::IsNearlyEqual(CurrentHealth, 0.0f);
}

void UHealth::OnDamageTaken(
	AActor* DamagedActor,
	float Damage, 
	const class UDamageType* DamageType,
	class AController* InstigatedBy,
	AActor* DamageCauser)
{
	ApplyDamage(Damage);

	if(IsDead() && GameMode)
	{
		GameMode->ActorDied(GetOwner());
	}
}

