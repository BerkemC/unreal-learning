// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAI.h"

#include "ShooterSamCharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void AShooterAI::BeginPlay()
{
	Super::BeginPlay();
}

void AShooterAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// if(!PlayerPawn || !LineOfSightTo(PlayerPawn))
	// {
	// 	StopMovement();
	// 	ClearFocus(EAIFocusPriority::Gameplay);
	// 	return;
	// }
	//
	// SetFocus(PlayerPawn);
	// MoveToActor(PlayerPawn, 200.0f);
}

void AShooterAI::StartBehaviourTree(AShooterSamCharacter* PlayerCharacter)
{
	if(!BehaviorTree)
	{
		return;
	}

	SelfCharacter = Cast<AShooterSamCharacter>(GetPawn());
	
	if(!Player)
	{
		Player = PlayerCharacter;
	}
	
	RunBehaviorTree(BehaviorTree);

	if(UBlackboardComponent* BlackBoard = GetBlackboardComponent())
	{
		BlackBoard->SetValueAsVector("PlayerLocation", Player->GetActorLocation());
		BlackBoard->SetValueAsVector("StartLocation", SelfCharacter->GetActorLocation());
	}
}