// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_LastPlayerLocation.h"

#include "ShooterAI.h"
#include "ShooterSamCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UBTService_LastPlayerLocation::UBTService_LastPlayerLocation()
{
	NodeName = TEXT("Update Last Known Player Location");
}

void UBTService_LastPlayerLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	if (const APawn* Player = UGameplayStatics::GetPlayerPawn(this, 0))
	{
		UBlackboardComponent* BlackBoard = OwnerComp.GetBlackboardComponent();

		if (!Player || !BlackBoard)
		{
			return;
		}
		
		BlackBoard->SetValueAsVector(GetSelectedBlackboardKey(), Player->GetActorLocation());
	}
}
