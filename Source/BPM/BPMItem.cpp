// Fill out your copyright notice in the Description page of Project Settings.


#include "BPMItem.h"
#include "Components/BoxComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ABPMItem::ABPMItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("ItemBoxComponent"));
	BoxComponent->InitBoxExtent(FVector(5.f, 5.f, 5.f));
	BoxComponent->SetCollisionProfileName(TEXT("OverlapAll"));
	BoxComponent->SetGenerateOverlapEvents(true);
	SetActorEnableCollision(true);
	
	SetRootComponent(BoxComponent);
	
	MeshItem = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	MeshItem->SetCollisionProfileName(TEXT("Item"));
	MeshItem->SetupAttachment(RootComponent);
	
}

// Called when the game starts or when spawned
void ABPMItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABPMItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	TArray<AActor*> OverlappingActors;
	BoxComponent->GetOverlappingActors(OverlappingActors);
	for (AActor* Actor : OverlappingActors)
	{
		//UE_LOG(LogTemp, Warning, TEXT("%s is overlapping with %s"), *GetName(), *Actor->GetName());
	}
	if(OverlappingActors.IsEmpty())
	{
		BoxComponent->SetRelativeLocation(BoxComponent->GetRelativeLocation() - FVector(0.f, 0.f, 600.f * DeltaTime));
	}
	
	FRotator Rotation = MeshItem->GetRelativeRotation();
	MeshItem->SetRelativeRotation(Rotation + FRotator(0.f, 180.f * DeltaTime, 0.f));
}

