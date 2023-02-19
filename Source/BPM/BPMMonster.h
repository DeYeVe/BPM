// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BPMMonster.generated.h"

UCLASS()
class BPM_API ABPMMonster : public ACharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, Category=Mesh)
	USkeletalMeshComponent* MeshMonster;
	USkeletalMeshComponent* GetMeshMonster() const { return MeshMonster; }
	
	UPROPERTY(VisibleAnywhere)
	class UBPMAnimInstance* AnimInstance;

public:
	// Sets default values for this character's properties
	ABPMMonster();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY()
	int Damage;

	UPROPERTY()
	int MaxHP;

	UPROPERTY()
	int CurHP;

	UPROPERTY()
	float MoveSpeed;

public:
	UFUNCTION()
	int GetDamage() const { return Damage; };

	//UFUNCTION()
	//void Die();
};
