// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelTransferVolume.h"

#include "BPMCharacter.h"
#include "Engine/LevelStreaming.h"
#include "Engine/Classes/Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "BPMGameInstance.h"
#include "BPMGameMode.h"
#include "BPMMonster.h"
#include "Components/AudioComponent.h"

// Sets default values
ALevelTransferVolume::ALevelTransferVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	TransferVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("TransferVolume"));
	RootComponent = TransferVolume;
	TransferVolume->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));

}

// Called when the game starts or when spawned
void ALevelTransferVolume::BeginPlay()
{
	Super::BeginPlay();
	
	BPMGameMode = Cast<ABPMGameMode>(GetWorld()->GetAuthGameMode());
	
}

// Called every frame
void ALevelTransferVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABPMMonster::StaticClass(), Actors);

	if (Actors.Num() == 0)
		IsEnable = true;

}

void ALevelTransferVolume::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);


	if(!IsEnable)
		return;
	
	if (OtherActor->IsA(ABPMCharacter::StaticClass()))
	{
		UBPMGameInstance* BPMGameInstance = Cast<UBPMGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
		ABPMCharacter* Player = Cast<ABPMCharacter>(OtherActor);
		
		/*
		BPMGameInstance->PlayerCurHp = Player->GetCurHP();
		BPMGameInstance->PlayerCurAmmo = Player->GetCurAmmo();
		BPMGameInstance->PlayerMaxAmmo = Player->GetMaxAmmo();
		BPMGameInstance->PlayerSpeed = Player->GetSpeed();

		ABPMGameMode* GameMode = Cast<ABPMGameMode>(GetWorld()->GetAuthGameMode());
		BPMGameInstance->TimerLastBeat = GameMode->TimerActor->FLastBeat;
		BPMGameInstance->TimerOffset = GameMode->TimerActor->FTotalTime;

		BPMGameInstance->BGMOffset = GameMode->TimerActor->FTotalTime - 0.1f;
		*/

		BPMGameInstance->IsRoomClear.Emplace(CurrentLevelName, true);
		
		ULevelStreaming* StreamingLevel = UGameplayStatics::GetStreamingLevel(GetWorld(), TransferLevelName);
		
		// unload
		ULevelStreaming* CurrentStreamingLevel = UGameplayStatics::GetStreamingLevel(GetWorld(), CurrentLevelName);
		
		FLatentActionInfo LatentAction;
		LatentAction.CallbackTarget = this;
		LatentAction.ExecutionFunction = "Completed";
		LatentAction.UUID = 1;
		LatentAction.Linkage = 0;

		if (CurrentStreamingLevel && CurrentStreamingLevel->IsLevelLoaded())
		{
			CurrentStreamingLevel->GetLoadedLevel()->RemoveFromRoot();
			
			UGameplayStatics::UnloadStreamLevel(GetWorld(), CurrentLevelName, LatentAction, true);
		}

		// load
		if (!StreamingLevel->IsLevelLoaded())
		{
			StreamingLevel->SetShouldBeLoaded(true);
			StreamingLevel->SetShouldBeVisible(true);
			UGameplayStatics::LoadStreamLevel(GetWorld(), TransferLevelName, true, true, LatentAction);
		}

		BPMGameInstance->CurrentLevelName = TransferLevelName;
		
		// move player
		Player->SetActorLocation(TransferLocation);
		Player->SetActorRotation(TransferRotator);
	}
}

