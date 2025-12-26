// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Health.generated.h"

class ABattleBlasterGamerMode;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLEBLASTER_API UHealth : public UActorComponent
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	float MaxHealth = 100.0f;
	
	// Sets default values for this component's properties
	UHealth();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void ResetHealth();
	void ApplyDamage(float Damage);
	bool IsDead() const;

	UFUNCTION()
	void OnDamageTaken(
		AActor* DamagedActor,
		float Damage,
		const class UDamageType* DamageType,
		class AController* InstigatedBy,
		AActor* DamageCauser );
	
private:
	UPROPERTY(VisibleAnywhere)
	float CurrentHealth;

	UPROPERTY()
	ABattleBlasterGamerMode* GameMode;
};
