// Fill out your copyright notice in the Description page of Project Settings.


#include "BPMHUDWidget.h"

void UBPMHUDWidget::OnPlayerHit()
{
	bIsHit = true;
	HitAlpha = 0.5f;
	UE_LOG(LogTemp, Log, TEXT("OnPlayerHit"));
}