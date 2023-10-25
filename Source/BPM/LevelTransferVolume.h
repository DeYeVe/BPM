// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelTransferVolume.generated.h"

UCLASS()
class BPM_API ALevelTransferVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelTransferVolume();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	FName TransferLevelName;
	
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	FName CurrentLevelName;
	
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	FVector TransferLocation;
	
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	FRotator TransferRotator;

	UPROPERTY()
	class ABPMGameMode* BPMGameMode;

	UPROPERTY()
	class UBoxComponent* TransferVolume;

	UPROPERTY()
	bool IsEnable;
};