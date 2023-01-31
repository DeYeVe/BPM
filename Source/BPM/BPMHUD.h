// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BPMHUD.generated.h"

/**
 * 
 */
UCLASS()
class BPM_API ABPMHUD : public AHUD
{
	GENERATED_BODY()

public:
	ABPMHUD();

protected:
	virtual void BeginPlay() override;
	
public:
	virtual void DrawHUD() override;

protected:
	UPROPERTY(EditDefaultsOnly)
	UTexture2D* CrosshairTexture;
	
	UPROPERTY(EditDefaultsOnly)
	UTexture2D* CrosshairLeftTexture;
	
	UPROPERTY(EditDefaultsOnly)
	UTexture2D* CrosshairRightTexture;
	
	UPROPERTY(EditDefaultsOnly)
	UTexture2D* CrosshairLeftSmallTexture;
	
	UPROPERTY(EditDefaultsOnly)
	UTexture2D* CrosshairRightSmallTexture;

public:
	UPROPERTY()
	class ABPMTimerActor* TimerActor;
};
