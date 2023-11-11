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
	
public:
	UPROPERTY(VisibleAnywhere)
	float FLastBeat;
	
	UPROPERTY(VisibleAnywhere)
	float FTotalTime;

	UPROPERTY(VisibleAnywhere)
	float FCrotchet = 60.f / 88.f; // 60 / BPM	

public:
	UFUNCTION()
	bool IsInCrotchet();
	
	UFUNCTION()
	bool IsInQuaver();

	UFUNCTION()
	float GetBeatOffset() const { return FTotalTime - FLastBeat; };
	
	UFUNCTION()
	float GetCrotchet() const { return FCrotchet; };
	
	UFUNCTION()
	float GetQuaver() const { return FCrotchet / 2.f; };
};
