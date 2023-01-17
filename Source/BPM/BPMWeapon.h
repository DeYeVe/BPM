// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TP_WeaponComponent.h"
#include "GameFramework/Actor.h"
#include "BPMWeapon.generated.h"

UCLASS()
class BPM_API ABPMWeapon : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	USkeletalMeshComponent* WeaponMesh;
	
public:	
	// Sets default values for this actor's properties
	ABPMWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere)
	UTP_WeaponComponent* WeaponComponent;
	
	UPROPERTY()
	class UBPMAnimInstance* AnimInstance;

	UTP_WeaponComponent* GetWeaponComponent() const { return WeaponComponent; }
	USkeletalMeshComponent* GetWeaponMesh() const { return WeaponMesh; }
	
public:
	void Fire();
	
	void Reload();
};
