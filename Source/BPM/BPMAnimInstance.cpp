// Fill out your copyright notice in the Description page of Project Settings.


#include "BPMAnimInstance.h"

UBPMAnimInstance::UBPMAnimInstance()
{
	auto InitMontage = [this](const FString& MontagePath, UAnimMontage*& Montage)
	{
		ConstructorHelpers::FObjectFinder<UAnimMontage> MontageFinder(*MontagePath);
		if (MontageFinder.Succeeded())
		{
			Montage = MontageFinder.Object;
		}
	};

	InitMontage(TEXT("AnimMontage'/Game/Player/AM_PlayerFire.AM_PlayerFire'"), PlayerFireMontage);
	InitMontage(TEXT("AnimMontage'/Game/Weapons/AM_PistolFire.AM_PistolFire'"), PistolFireMontage);
	InitMontage(TEXT("AnimMontage'/Game/Player/AM_PlayerReloadStart.AM_PlayerReloadStart'"), PlayerReloadStartMontage);
	InitMontage(TEXT("AnimMontage'/Game/Weapons/AM_PistolReloadStart.AM_PistolReloadStart'"), PistolReloadStartMontage);
	InitMontage(TEXT("AnimMontage'/Game/Player/AM_PlayerReloadEnd.AM_PlayerReloadEnd'"), PlayerReloadEndMontage);
	InitMontage(TEXT("AnimMontage'/Game/Weapons/AM_PistolReloadEnd.AM_PistolReloadEnd'"), PistolReloadEndMontage);
	InitMontage(TEXT("AnimMontage'/Game/Monsters/Scorpion/AM_ScorpionAttack.AM_ScorpionAttack'"), ScorpionAttackMontage);
	InitMontage(TEXT("AnimMontage'/Game/Monsters/DarkKnight/AM_DarkKnightAttack1.AM_DarkKnightAttack1'"), DarkKinightAttack1Monatage);
	InitMontage(TEXT("AnimMontage'/Game/Monsters/DarkKnight/AM_DarkKnightAttack2.AM_DarkKnightAttack2'"), DarkKinightAttack2Monatage);
	InitMontage(TEXT("AnimMontage'/Game/Monsters/DarkKnight/AM_DarkKnightSpawn.AM_DarkKnightSpawn'"), DarkKinightSpawnMonatage);
	InitMontage(TEXT("AnimMontage'/Game/Monsters/DarkKnight/AM_DarkKnightWalkLeft.AM_DarkKnightWalkLeft'"), DarkKinightWalkLeftMonatage);
	InitMontage(TEXT("AnimMontage'/Game/Monsters/DarkKnight/AM_DarkKnightWalkRight.AM_DarkKnightWalkRight'"), DarkKinightWalkRightMonatage);

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
