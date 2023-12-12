// Fill out your copyright notice in the Description page of Project Settings.


#include "BPMHUDWidget.h"

void UBPMHUDWidget::SetVisibleSwapImage(bool b)
{
	if(b)
		Swap->SetVisibility(ESlateVisibility::Visible);
	else
	{
		Swap->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UBPMHUDWidget::OnPlayerHit()
{
	bIsHit = true;
	HitAlpha = 0.5f;
}
