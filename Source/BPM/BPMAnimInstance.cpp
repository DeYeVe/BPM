// Fill out your copyright notice in the Description page of Project Settings.


#include "BPMAnimInstance.h"

UBPMAnimInstance::UBPMAnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> PlayerFireAM(TEXT("AnimMontage'/Game/Player/AM_PlayerFire.AM_PlayerFire'"));
	if (PlayerFireAM.Succeeded())
	{
		PlayerFireMontage = PlayerFireAM.Object;
	}
	
	static ConstructorHelpers::FObjectFinder<UAnimMontage> PistolFireAM(TEXT("AnimMontage'/Game/Weapons/AM_PistolFire.AM_PistolFire'"));
	if (PistolFireAM.Succeeded())
	{
		PistolFireMontage = PistolFireAM.Object;
	}
	
	static ConstructorHelpers::FObjectFinder<UAnimMontage> PlayerReloadStartAM(TEXT("AnimMontage'/Game/Player/AM_PlayerReloadStart.AM_PlayerReloadStart'"));
	if (PlayerReloadStartAM.Succeeded())
	{
		PlayerReloadStartMontage = PlayerReloadStartAM.Object;
	}
	
	static ConstructorHelpers::FObjectFinder<UAnimMontage> PistolReloadStartAM(TEXT("AnimMontage'/Game/Weapons/AM_PistolReloadStart.AM_PistolReloadStart'"));
	if (PistolReloadStartAM.Succeeded())
	{
		PistolReloadStartMontage = PistolReloadStartAM.Object;
	}
	
	static ConstructorHelpers::FObjectFinder<UAnimMontage> PlayerReloadEndAM(TEXT("AnimMontage'/Game/Player/AM_PlayerReloadEnd.AM_PlayerReloadEnd'"));
	if (PlayerReloadEndAM.Succeeded())
	{
		PlayerReloadEndMontage = PlayerReloadEndAM.Object;
	}
	
	static ConstructorHelpers::FObjectFinder<UAnimMontage> PistolReloadEndAM(TEXT("AnimMontage'/Game/Weapons/AM_PistolReloadEnd.AM_PistolReloadEnd'"));
	if (PistolReloadEndAM.Succeeded())
	{
		PistolReloadEndMontage = PistolReloadEndAM.Object;
	}
	
}

void UBPMAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
}

void UBPMAnimInstance::PlayPlayerFireMontage()
{
	Montage_Play(PlayerFireMontage);
}

void UBPMAnimInstance::PlayPistolFireMontage()
{
	Montage_Play(PistolFireMontage);
}

void UBPMAnimInstance::PlayPlayerReloadStartMontage()
{
	Montage_Play(PlayerReloadStartMontage);
}

void UBPMAnimInstance::PlayPistolReloadStartMontage()
{
	Montage_Play(PistolReloadStartMontage);
}

void UBPMAnimInstance::PlayPlayerReloadEndMontage()
{
	Montage_Play(PlayerReloadEndMontage);
}

void UBPMAnimInstance::PlayPistolReloadEndMontage()
{
	Montage_Play(PistolReloadEndMontage);
}
