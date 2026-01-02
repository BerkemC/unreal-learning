// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ClearBlackBoardValue.h"

#include "BehaviorTree/BlackboardComponent.h"

UBTTask_ClearBlackBoardValue::UBTTask_ClearBlackBoardValue()
{
	NodeName = TEXT("Clear Black Board Value");
}

EBTNodeResult::Type UBTTask_ClearBlackBoardValue::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	
	if(UBlackboardComponent* BlackBoard = OwnerComp.GetBlackboardComponent())
	{
		BlackBoard->ClearValue(GetSelectedBlackboardKey());
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
