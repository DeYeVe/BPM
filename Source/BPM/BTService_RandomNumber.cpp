// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_RandomNumber.h"
#include "BPMAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BPMDarkKnight.h"
#include "Kismet/GameplayStatics.h"

UBTService_RandomNumber::UBTService_RandomNumber()
{
	NodeName = TEXT("CreateRandomNumber");

	bCallTickOnSearchStart = true;
	
}

void UBTService_RandomNumber::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	
	int x = 0;
	x = FMath::RandRange(1, 100);

	if (x <= 40)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsInt(FName(TEXT("SelectAttackNumber")), 1);
	}
	else if (x <= 80)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsInt(FName(TEXT("SelectAttackNumber")), 2);
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsInt(FName(TEXT("SelectAttackNumber")), 3);
	}
	
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABPMDarkKnight::StaticClass(), FoundActors);

	if (FoundActors.Num() > 0)
	{
		DarkKnight = Cast<ABPMDarkKnight>(FoundActors[0]);

		if (DarkKnight)
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(FName(TEXT("IsDead")), DarkKnight->IsDead);
		}
	}
}
