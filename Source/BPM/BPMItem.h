// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BPMItem.generated.h"

UCLASS()
class BPM_API ABPMItem : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category=Mesh)
	class UStaticMeshComponent* MeshItem;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* BoxComponent;
	
public:	
	// Sets default values for this actor's properties
	ABPMItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
