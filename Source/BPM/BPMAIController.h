// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BPMAIController.generated.h"

/**
 * 
 */
UCLASS()
class BPM_API ABPMAIController : public AAIController
{
	GENERATED_BODY()

public:
	ABPMAIController();

	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

	UPROPERTY()
	class UBehaviorTree* BehaviorTree;

	UPROPERTY()
	class UBlackboardData* BlackboardData;
};
