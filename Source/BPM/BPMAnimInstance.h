// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BPMAnimInstance.generated.h"

#define DECLARE_ANIM_MONTAGE(CategoryPrefix, Name) \
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=CategoryPrefix, Meta=(AllowPrivateAccess=true)) \
	UAnimMontage* Name;

UCLASS()
class BPM_API UBPMAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UBPMAnimInstance();

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	void PlayPlayerFireMontage();
	void PlayPistolFireMontage();
	void PlayPlayerReloadStartMontage();
	void PlayPistolReloadStartMontage();	
	void PlayPlayerReloadEndMontage();
	void PlayPistolReloadEndMontage();	
	void PlayScorpionAttackMontage();
	void PlayDarkKinightAttack1Monatage();
	void PlayDarkKinightAttack2Monatage();
	void PlayDarkKinightSpawnMonatage();
	void PlayDarkKinightWalkLeftMonatage();
	void PlayDarkKinightWalkRightMonatage();

private:
	enum STATE
	{
		IDLE,
		RELOAD
	};

	STATE State;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Player, Meta=(AllowPrivateAccess=true))
	bool CanAct;

	DECLARE_ANIM_MONTAGE(Player, PlayerFireMontage);
	DECLARE_ANIM_MONTAGE(Pistol, PistolFireMontage);
	DECLARE_ANIM_MONTAGE(Player, PlayerReloadStartMontage);
	DECLARE_ANIM_MONTAGE(Pistol, PistolReloadStartMontage);
	DECLARE_ANIM_MONTAGE(Player, PlayerReloadEndMontage);
	DECLARE_ANIM_MONTAGE(Pistol, PistolReloadEndMontage);
	DECLARE_ANIM_MONTAGE(Scorpion, ScorpionAttackMontage);
	DECLARE_ANIM_MONTAGE(DarkKnight, DarkKinightAttack1Monatage);
	DECLARE_ANIM_MONTAGE(DarkKnight, DarkKinightAttack2Monatage);
	DECLARE_ANIM_MONTAGE(DarkKnight, DarkKinightSpawnMonatage);
	DECLARE_ANIM_MONTAGE(DarkKnight, DarkKinightWalkLeftMonatage);
	DECLARE_ANIM_MONTAGE(DarkKnight, DarkKinightWalkRightMonatage);
};
