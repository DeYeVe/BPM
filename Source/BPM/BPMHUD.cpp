// Fill out your copyright notice in the Description page of Project Settings.


#include "BPMHUD.h"
#include "CanvasItem.h"
#include "Engine/Canvas.h"
#include "BPMTimerActor.h"
#include "Kismet/GameplayStatics.h"

ABPMHUD::ABPMHUD()
{
}

void ABPMHUD::BeginPlay()
{
	Super::BeginPlay();
	
	TimerActor = Cast<ABPMTimerActor>(UGameplayStatics::GetActorOfClass(GetWorld(), ABPMTimerActor::StaticClass()));

}

void ABPMHUD::DrawHUD()
{
	Super::DrawHUD();
	
	// Find the center of our canvas.
	FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);

	if (CrosshairTexture)
	{
		// Offset by half of the texture's dimensions so that the center of the texture aligns with the center of the Canvas.
		FVector2D CrossHairDrawPosition(Center.X - (CrosshairTexture->GetSurfaceWidth() * (Canvas->SizeX / 3200.f) * 0.5f),
			Center.Y - (CrosshairTexture->GetSurfaceHeight() * (Canvas->SizeX / 3200.f) * 0.5f));

		DrawTextureSimple(CrosshairTexture, CrossHairDrawPosition.X, CrossHairDrawPosition.Y,Canvas->SizeX / 3200.f);

		if(CrosshairLeftTexture && CrosshairRightTexture && CrosshairLeftSmallTexture && CrosshairRightSmallTexture)
		{			
			float SideOffset = 80 * (TimerActor->GetBeatOffset() / TimerActor->GetCrotchet());
			float SideOffsetSmall;
			if(TimerActor->GetBeatOffset() >= TimerActor->GetQuaver())
			{
				SideOffsetSmall = 80 * ((TimerActor->GetBeatOffset() - TimerActor->GetQuaver()) / TimerActor->GetCrotchet());
			}
			else
			{
				SideOffsetSmall = 80 * ((TimerActor->GetBeatOffset() + TimerActor->GetQuaver()) / TimerActor->GetCrotchet());
			}
			
			DrawTextureSimple(CrosshairLeftTexture, CrossHairDrawPosition.X - 80.f + SideOffset, CrossHairDrawPosition.Y,Canvas->SizeX / 3200.f);
			DrawTextureSimple(CrosshairLeftTexture, CrossHairDrawPosition.X - 160.f + SideOffset, CrossHairDrawPosition.Y,Canvas->SizeX / 3200.f);
			DrawTextureSimple(CrosshairRightTexture, CrossHairDrawPosition.X + 80.f - SideOffset, CrossHairDrawPosition.Y,Canvas->SizeX / 3200.f);
			DrawTextureSimple(CrosshairRightTexture, CrossHairDrawPosition.X + 160.f - SideOffset, CrossHairDrawPosition.Y,Canvas->SizeX / 3200.f);
			DrawTextureSimple(CrosshairLeftSmallTexture, CrossHairDrawPosition.X - 80.f + SideOffsetSmall, CrossHairDrawPosition.Y,Canvas->SizeX / 3200.f);
			DrawTextureSimple(CrosshairLeftSmallTexture, CrossHairDrawPosition.X - 160.f + SideOffsetSmall, CrossHairDrawPosition.Y,Canvas->SizeX / 3200.f);
			DrawTextureSimple(CrosshairRightSmallTexture, CrossHairDrawPosition.X + 80.f - SideOffsetSmall, CrossHairDrawPosition.Y,Canvas->SizeX / 3200.f);
			DrawTextureSimple(CrosshairRightSmallTexture, CrossHairDrawPosition.X + 160.f - SideOffsetSmall, CrossHairDrawPosition.Y,Canvas->SizeX / 3200.f);

		}
	}
}