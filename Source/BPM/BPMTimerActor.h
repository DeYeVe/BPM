// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BPMTimerActor.generated.h"

UCLASS()
class BPM_API ABPMTimerActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABPMTimerActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
private:
	UPROPERTY(VisibleAnywhere)
	float FLastBeat;
	
	UPROPERTY(VisibleAnywhere)
	float FTotalTime = 0.1f;

	UPROPERTY(VisibleAnywhere)
	float FCrotchet = 60.f / 88.f; // 60 / BPM	

	public:
	UFUNCTION()
	bool IsInCrotchet();
	
	UFUNCTION()
	bool IsInQuaver();
};
