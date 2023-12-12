// Fill out your copyright notice in the Description page of Project Settings.


#include "BPMScorpion.h"

#include "BPMAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/DamageEvents.h"

ABPMScorpion::ABPMScorpion()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SM(TEXT("SkeletalMesh'/Game/Monsters/Scorpion/Scorpion.Scorpion'"));

	if (SM.Succeeded())
	{
		MeshMonster->SetSkeletalMesh(SM.Object);
	}
	
	MeshMonster->SetRelativeLocation(FVector(20.0f, 0.0f, -50.f));
	MeshMonster->SetRelativeScale3D(FVector(1.f, 1.f, 1.f));
	MeshMonster->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	MaxHP = 200;
	CurHP = MaxHP;
	MoveSpeed = 300.f;
	AttackCoolDown = 2.f;
}

void ABPMScorpion::BeginPlay()
{
	Super::BeginPlay();
}

void ABPMScorpion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(IsAttacking)
	{		
		AttackCoolDown -= DeltaTime;
		if(AttackCoolDown <= 0)
		{
			IsAttacking = false;
			AttackCoolDown = 2.0f;
		}
		else
			return;
	}
	
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	FVector PlayerLocation = PlayerPawn->GetActorLocation();
	FVector MonsterLocation = GetActorLocation();
	FVector Direction = PlayerLocation - MonsterLocation;
	FVector NormalDirection = Direction;
	NormalDirection.Normalize();
	
	SetActorRotation(NormalDirection.Rotation());

	if (Direction.Size() > 200.f) //move
		{
		NormalDirection.Z = 0.f;
		GetCharacterMovement()->MoveSmooth((NormalDirection * MoveSpeed), DeltaTime);
		}
	else // attack
	{
		IsAttacking = true;

		FHitResult HitResult;
		FCollisionQueryParams Params(NAME_None, false, this);

		float AttackRange = 100.f;
		float AttackRadius = 50.f;

		bool bResult = GetWorld()->SweepSingleByChannel(
			OUT HitResult,
			GetActorLocation(),
			GetActorLocation() + GetActorForwardVector() * AttackRange,
			FQuat::Identity,
			ECollisionChannel::ECC_GameTraceChannel5,
			FCollisionShape::MakeSphere(AttackRadius),
			Params);

		FVector Vec = GetActorForwardVector() * AttackRange;
		FVector Center = GetActorLocation() + Vec * 0.5f;
		float HalfHeight = AttackRange * 0.5f + AttackRadius;
		FQuat Rotation = FRotationMatrix::MakeFromZ(Vec).ToQuat();
		FColor DrawColor;
		if(bResult)
			DrawColor = FColor::Green;
		else
			DrawColor = FColor::Red;
	
		//DrawDebugCapsule(GetWorld(), Center, HalfHeight, AttackRadius, Rotation, DrawColor, false, 2.f);
	
		if(bResult && IsValid(HitResult.GetActor()))
		{
			FDamageEvent DamageEvent;
			HitResult.GetActor()->TakeDamage(GetDamage(), DamageEvent, GetController(), this);
		}

		if (AnimInstance != nullptr)
		{
			AnimInstance->PlayScorpionAttackMontage();
		}
	}
}

void ABPMScorpion::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
