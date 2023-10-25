// Fill out your copyright notice in the Description page of Project Settings.


#include "BPMGameInstance.h"

void UBPMGameInstance::Init()
{
	Super::Init();

	IsRoomClear.Add(TEXT("Room1"), false);
	IsRoomClear.Add(TEXT("Room2"), false);
	IsRoomClear.Add(TEXT("Room3"), false);
	IsRoomClear.Add(TEXT("Room4"), false);
	IsRoomClear.Add(TEXT("Room5"), false);

	TimerOffset = 0.08f;
	TimerLastBeat = 0.f;
	BGMOffset = 0.f;
	PlayerCurHp = 100;
	PlayerCurAmmo = 8;
	PlayerMaxAmmo = 8;
	PlayerSpeed = 600.f;

	CurrentLevelName = TEXT("Room1");
}
