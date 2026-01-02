// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_Shoot.h"

#include "ShooterAI.h"
#include "ShooterSamCharacter.h"

UBTTaskNode_Shoot::UBTTaskNode_Shoot()
{
	NodeName = TEXT("Shoot");
}

EBTNodeResult::Type UBTTaskNode_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if(const AShooterAI* ShooterAI = Cast<AShooterAI>(OwnerComp.GetAIOwner()))
	{
		if(ShooterAI->Player && ShooterAI->Player->GetIsAlive())
		{
			ShooterAI->SelfCharacter->Shoot();
			return EBTNodeResult::Succeeded;	
		}
	}

	return EBTNodeResult::Failed;
}
