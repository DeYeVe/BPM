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
	TMap<FName, bool> IsRoomClear;
	int PlayerCurHp;
	int PlayerCurAmmo;
	int PlayerMaxAmmo;
	float PlayerSpeed;
	float TimerOffset;
	float TimerLastBeat;
	float BGMOffset;
	FName CurrentLevelName;
	
};
