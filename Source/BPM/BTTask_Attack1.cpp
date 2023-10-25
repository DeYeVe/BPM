// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Attack1.h"
#include "AIController.h"
#include "BPMDarkKnight.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_Attack1::UBTTask_Attack1()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_Attack1::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto DarkKnight = Cast<ABPMDarkKnight>(OwnerComp.GetAIOwner()->GetPawn());
	if (DarkKnight == nullptr)
		return EBTNodeResult::Failed;

	DarkKnight->Attack1();

	return Result;
}