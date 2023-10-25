// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BPMDoor.generated.h"

UCLASS()
class BPM_API ABPMDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABPMDoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:	
	UPROPERTY(EditAnywhere)
	bool bIsLeftDoor;

	UPROPERTY()
	bool bIsInClearedRoom;
	
	UPROPERTY()
	bool bIsOpening;

	UPROPERTY()
	float OpeningTime;

	UPROPERTY()
	FRotator Rotaion;
	
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	FName CurrentLevelName;	
};
