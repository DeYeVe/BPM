// Fill out your copyright notice in the Description page of Project Settings.


#include "BPMTimerActor.h"

// Sets default values
ABPMTimerActor::ABPMTimerActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABPMTimerActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABPMTimerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	FTotalTime += DeltaTime;

	if(FTotalTime - FLastBeat >= FCrotchet)
	{
		FLastBeat += FCrotchet;		
		UE_LOG(LogTemp, Log, TEXT("%f"), FLastBeat);
	}
}

bool ABPMTimerActor::IsInCrotchet()
{
	if (FLastBeat + 0.1f >= FTotalTime || FLastBeat + FCrotchet - 0.1f <= FTotalTime)
		return true;

	return false;
}

bool ABPMTimerActor::IsInQuaver()
{
	if (FLastBeat + FCrotchet / 2.f - 0.1f <= FTotalTime && FLastBeat + FCrotchet / 2.f + 0.1f >= FTotalTime)
		return true;
	
	return  false;
}
