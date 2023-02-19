// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BPMTimerActor.h"
#include "GameFramework/GameModeBase.h"
#include "BPMGameMode.generated.h"

UCLASS(minimalapi)
class ABPMGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABPMGameMode();

	UPROPERTY()
	AActor* BGMActor;
	
	UPROPERTY()
	UAudioComponent* BGMComponent;

	UPROPERTY()
	class USoundCue* BGMSoundCue;

	UPROPERTY()
	ABPMTimerActor* TimerActor;
	
	UPROPERTY()
	TSubclassOf<UUserWidget> HUDWidget;

	UPROPERTY()
	UUserWidget* CurWidget;

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
};



