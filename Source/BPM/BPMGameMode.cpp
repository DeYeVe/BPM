// Copyright Epic Games, Inc. All Rights Reserved.

#include "BPMGameMode.h"
#include "UObject/ConstructorHelpers.h"

ABPMGameMode::ABPMGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("Blueprint'/Game/Player/BP_BPMPlayer.BP_BPMPlayer_C'"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}