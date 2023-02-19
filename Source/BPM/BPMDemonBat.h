// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BPMMonster.h"
#include "GameFramework/Character.h"
#include "BPMDemonBat.generated.h"

UCLASS()
class BPM_API ABPMDemonBat : public ABPMMonster
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABPMDemonBat();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	float MoveIntervalTime;

	float AttackCoolDown;

public:
	UPROPERTY(EditDefaultsOnly, Category=Projectile)
	TSubclassOf<class ABPMProjectile> ProjectileClass;
};
