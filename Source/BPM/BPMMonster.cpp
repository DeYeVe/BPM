// Fill out your copyright notice in the Description page of Project Settings.


#include "BPMMonster.h"
#include "Components/CapsuleComponent.h"
#include "BPMAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ABPMMonster::ABPMMonster()
{
	GetCapsuleComponent()->InitCapsuleSize(30.f, 40.0f);
	
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshMonster = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MonsterMesh"));
	MeshMonster->SetupAttachment(GetCapsuleComponent());
	MeshMonster->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	
}

// Called when the game starts or when spawned
void ABPMMonster::BeginPlay()
{
	Super::BeginPlay();
	
	AnimInstance = Cast<UBPMAnimInstance>(GetMeshMonster()->GetAnimInstance());
	
}

// Called every frame
void ABPMMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurHP <= 0)
	{
		//DropItem
		Destroy();
	}

}

// Called to bind functionality to input
void ABPMMonster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

