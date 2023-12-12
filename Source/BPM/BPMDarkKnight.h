// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BPMMonster.h"
#include "BPMDarkKnight.generated.h"

/**
 * 
 */
UCLASS()
class BPM_API ABPMDarkKnight : public ABPMMonster
{
	GENERATED_BODY()
	
public:
	// Sets default values for this character's properties
	ABPMDarkKnight();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(EditDefaultsOnly, Category=Projectile)
	TSubclassOf<class ABPMProjectile> ProjectileClass;

public:
	UPROPERTY(EditDefaultsOnly, Category=Projectile)
	TSubclassOf<class ABPMElemental> ElementalClass;
	
public:
	UFUNCTION(BlueprintCallable)
	void Attack1();

	UFUNCTION(BlueprintCallable)
	void Attack2();

	UFUNCTION(BlueprintCallable)
	void SpawnMonster();

	UFUNCTION(BlueprintCallable)
	void StartWalk() {IsWalking = true;};

	bool IsWalking;
	bool IsWalkingLeft;
	bool IsWalkingRight;
	float WalkTime;

	UPROPERTY(EditAnywhere)
	bool IsDead;
};
