// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "BPMGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class BPM_API UBPMGameInstance : public UGameInstance
{
	GENERATED_BODY()

	virtual void Init() override;

public:
	UPROPERTY()
	TMap<FName, bool> IsRoomClear;

	UPROPERTY()
	int PlayerCurHp;

	UPROPERTY()
	int PlayerCurAmmo;

	UPROPERTY()
	int PlayerMaxAmmo;
	
	UPROPERTY()
	float PlayerSpeed;
	
	UPROPERTY()
	float TimerOffset;
	
	UPROPERTY()
	float TimerLastBeat;
	
	UPROPERTY()
	float BGMOffset;

	UPROPERTY()
	FName CurrentLevelName;
	
};
