// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerLocationIfSeen.h"

#include "AIController.h"
#include "ShooterAI.h"
#include "ShooterSamCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_PlayerLocationIfSeen::UBTService_PlayerLocationIfSeen()
{
	NodeName = TEXT("Update Player Location If Seen");
}

void UBTService_PlayerLocationIfSeen::TickNode(
	UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory,
	const float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	if (AShooterAI* ShooterAI = Cast<AShooterAI>(OwnerComp.GetAIOwner()))
	{
		AShooterSamCharacter* Player = ShooterAI->Player;
		UBlackboardComponent* BlackBoard = OwnerComp.GetBlackboardComponent();

		if (!Player || !BlackBoard || !ShooterAI->LineOfSightTo(Player))
		{
			ShooterAI->ClearFocus(EAIFocusPriority::Gameplay);
			BlackBoard->ClearValue(GetSelectedBlackboardKey());
			return;
		}

		ShooterAI->SetFocus(Player);
		BlackBoard->SetValueAsVector(GetSelectedBlackboardKey(), Player->GetActorLocation());
	}
}
