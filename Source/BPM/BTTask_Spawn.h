// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Spawn.generated.h"

/**
 * 
 */
UCLASS()
class BPM_API UBTTask_Spawn : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_Spawn();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
