// Fill out your copyright notice in the Description page of Project Settings.


#include "BPMAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

ABPMAIController::ABPMAIController()
{
	/*static ConstructorHelpers::FObjectFinder<UBehaviorTree> BT(TEXT("BlackboardData'/Game/AI/BB_Monster.BB_Monster'"));
	if (BT.Succeeded())
	{
		BehaviorTree = BT.Object;
	}
	
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BD(TEXT("BlackboardData'/Game/AI/BB_Monster.BB_Monster'"));
	if (BD.Succeeded())
	{
		BlackboardData = BD.Object;
	}*/
}

void ABPMAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	UBlackboardComponent* BlackboardComp = Blackboard.Get();
	if(UseBlackboard(BlackboardData, BlackboardComp))
	{
		if(RunBehaviorTree(BehaviorTree))
		{
			
		}
	}
	this->Blackboard = BlackboardComp;
}

void ABPMAIController::OnUnPossess()
{
	Super::OnUnPossess();
	
	
}
