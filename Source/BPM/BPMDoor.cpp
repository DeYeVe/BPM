// Fill out your copyright notice in the Description page of Project Settings.


#include "BPMDoor.h"

#include "BPMGameInstance.h"
#include "BPMMonster.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABPMDoor::ABPMDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABPMDoor::BeginPlay()
{
	Super::BeginPlay();
	
	Rotaion = GetActorRotation();

	UBPMGameInstance* BPMGameInstance = Cast<UBPMGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	bIsInClearedRoom = *(BPMGameInstance->IsRoomClear.Find(CurrentLevelName));
	
	if(bIsInClearedRoom)
	{
		if(bIsLeftDoor)
		{
			SetActorRotation(Rotaion + FRotator(0.f, -70.f, 0.f));
		}
		else
		{			
			SetActorRotation(Rotaion + FRotator(0.f, 70.f, 0.f));			
		}
	}	
}

// Called every frame
void ABPMDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsOpening)
	{
		OpeningTime += DeltaTime;

		if(OpeningTime >= 2.0f)
		{
			OpeningTime = 2.0;
			bIsOpening = false;
			bIsInClearedRoom = true;
		}

		if(bIsLeftDoor)
		{
			SetActorRotation(Rotaion + FRotator(0.f, - OpeningTime * 35.f, 0.f));
		}
		else
		{			
			SetActorRotation(Rotaion + FRotator(0.f, OpeningTime * 35.f, 0.f));			
		}
	}
	
	else if (!bIsInClearedRoom)
	{
		TArray<AActor*> Actors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABPMMonster::StaticClass(), Actors);

		if (Actors.Num() == 0)
			bIsOpening = true;		
	}

}

