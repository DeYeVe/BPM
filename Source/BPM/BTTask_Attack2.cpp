// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Attack2.h"
#include "AIController.h"
#include "BPMDarkKnight.h"

UBTTask_Attack2::UBTTask_Attack2()
{
	//bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_Attack2::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto DarkKnight = Cast<ABPMDarkKnight>(OwnerComp.GetAIOwner()->GetPawn());
	if (DarkKnight == nullptr)
		return EBTNodeResult::Failed;

	DarkKnight->Attack2();

	return Result;
}