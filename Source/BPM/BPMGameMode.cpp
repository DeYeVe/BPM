// Copyright Epic Games, Inc. All Rights Reserved.

#include "BPMGameMode.h"
#include "UObject/ConstructorHelpers.h"
#include "BPMHUD.h"
#include "BPMHUDWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"

ABPMGameMode::ABPMGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("Blueprint'/Game/Player/BP_BPMPlayer.BP_BPMPlayer_C'"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	//sound
	static ConstructorHelpers::FObjectFinder<USoundCue> SoundCueBase(TEXT("SoundCue'/Game/Sounds/SQ_BGM.SQ_BGM'"));
	
	if (SoundCueBase.Succeeded())
	{
		BGMSoundCue = SoundCueBase.Object;
	}
	BGMComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	BGMComponent->SetSound(BGMSoundCue);
	BGMActor = CreateDefaultSubobject<AActor>(TEXT("BGMActor"));
	BGMComponent->SetupAttachment(BGMActor->GetRootComponent());

	// hud
	static ConstructorHelpers::FClassFinder<AHUD> HUDClassFinder(TEXT("Blueprint'/Game/UI/BP_HUD.BP_HUD_C'"));
	HUDClass =  HUDClassFinder.Class;

	static ConstructorHelpers::FClassFinder<UBPMHUDWidget> HUDWidgetClassFinder(TEXT("WidgetBlueprint'/Game/UI/WBP_HUD.WBP_HUD_C'"));

	if(HUDWidgetClassFinder.Succeeded())
	{
		HUDWidget =  HUDWidgetClassFinder.Class;
		CurWidget = CreateWidget(GetWorld(), HUDWidget);
		if(CurWidget)
		{
			CurWidget->AddToViewport();
		}
	}

	

}

void ABPMGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	BGMActor = GetWorld()->SpawnActor<AActor>(AActor::StaticClass());
	TimerActor = GetWorld()->SpawnActor<ABPMTimerActor>(ABPMTimerActor::StaticClass());
	BGMComponent->Play();
	
}

void ABPMGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
