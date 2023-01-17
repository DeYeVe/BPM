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
