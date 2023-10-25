// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Spawn.h"
#include "AIController.h"
#include "BPMDarkKnight.h"

UBTTask_Spawn::UBTTask_Spawn()
{
}

EBTNodeResult::Type UBTTask_Spawn::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto DarkKnight = Cast<ABPMDarkKnight>(OwnerComp.GetAIOwner()->GetPawn());
	if (DarkKnight == nullptr)
		return EBTNodeResult::Failed;

	DarkKnight->SpawnMonster();

	return Result;
}
