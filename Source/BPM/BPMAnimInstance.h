// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BPMAnimInstance.generated.h"

/**
 * 
 */
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

private:
	enum STATE
	{
		IDLE,
		RELOAD
	};

	STATE State;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Player, Meta=(AllowPrivateAccess=true))
	bool CanAct;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Player, Meta=(AllowPrivateAccess=true))
	UAnimMontage* PlayerFireMontage;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Pistol, Meta=(AllowPrivateAccess=true))
	UAnimMontage* PistolFireMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Player, Meta=(AllowPrivateAccess=true))
	UAnimMontage* PlayerReloadStartMontage;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Pistol, Meta=(AllowPrivateAccess=true))
	UAnimMontage* PistolReloadStartMontage;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Player, Meta=(AllowPrivateAccess=true))
	UAnimMontage* PlayerReloadEndMontage;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Pistol, Meta=(AllowPrivateAccess=true))
	UAnimMontage* PistolReloadEndMontage;
	
};
