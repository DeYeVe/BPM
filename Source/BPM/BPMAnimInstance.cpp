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
	
	static ConstructorHelpers::FObjectFinder<UAnimMontage> ScorpionAttackAM(TEXT("AnimMontage'/Game/Monsters/Scorpion/AM_ScorpionAttack.AM_ScorpionAttack'"));
	if (ScorpionAttackAM.Succeeded())
	{
		ScorpionAttackMontage = ScorpionAttackAM.Object;
	}
	
	static ConstructorHelpers::FObjectFinder<UAnimMontage> DarkKinightAttack1AM(TEXT("AnimMontage'/Game/Monsters/DarkKnight/AM_DarkKnightAttack1.AM_DarkKnightAttack1'"));
	if (DarkKinightAttack1AM.Succeeded())
	{
		DarkKinightAttack1Monatage = DarkKinightAttack1AM.Object;
	}
	
	static ConstructorHelpers::FObjectFinder<UAnimMontage> DarkKinightAttack2AM(TEXT("AnimMontage'/Game/Monsters/DarkKnight/AM_DarkKnightAttack2.AM_DarkKnightAttack2'"));
	if (DarkKinightAttack2AM.Succeeded())
	{
		DarkKinightAttack2Monatage = DarkKinightAttack2AM.Object;
	}
	
	static ConstructorHelpers::FObjectFinder<UAnimMontage> DarkKinightSpawnAM(TEXT("AnimMontage'/Game/Monsters/DarkKnight/AM_DarkKnightSpawn.AM_DarkKnightSpawn'"));
	if (DarkKinightSpawnAM.Succeeded())
	{
		DarkKinightSpawnMonatage = DarkKinightSpawnAM.Object;
	}
	
	static ConstructorHelpers::FObjectFinder<UAnimMontage> DarkKinightWalkLeftAM(TEXT("AnimMontage'/Game/Monsters/DarkKnight/AM_DarkKnightWalkLeft.AM_DarkKnightWalkLeft'"));
	if (DarkKinightWalkLeftAM.Succeeded())
	{
		DarkKinightWalkLeftMonatage = DarkKinightWalkLeftAM.Object;
	}
	
	static ConstructorHelpers::FObjectFinder<UAnimMontage> DarkKinightWalkRightAM(TEXT("AnimMontage'/Game/Monsters/DarkKnight/AM_DarkKnightWalkRight.AM_DarkKnightWalkRight'"));
	if (DarkKinightWalkRightAM.Succeeded())
	{
		DarkKinightWalkRightMonatage = DarkKinightWalkRightAM.Object;
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

void UBPMAnimInstance::PlayScorpionAttackMontage()
{
	Montage_Play(ScorpionAttackMontage);
}

void UBPMAnimInstance::PlayDarkKinightAttack1Monatage()
{
	Montage_Play(DarkKinightAttack1Monatage);
}

void UBPMAnimInstance::PlayDarkKinightAttack2Monatage()
{
	Montage_Play(DarkKinightAttack2Monatage);
}

void UBPMAnimInstance::PlayDarkKinightSpawnMonatage()
{
	Montage_Play(DarkKinightSpawnMonatage);
}

void UBPMAnimInstance::PlayDarkKinightWalkLeftMonatage()
{
	Montage_Play(DarkKinightWalkLeftMonatage);
}

void UBPMAnimInstance::PlayDarkKinightWalkRightMonatage()
{
	Montage_Play(DarkKinightWalkRightMonatage);
}
