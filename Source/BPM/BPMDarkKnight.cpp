// Fill out your copyright notice in the Description page of Project Settings.


#include "BPMDarkKnight.h"

#include "BPMAIController.h"
#include "BPMAnimInstance.h"
#include "BPMProjectile.h"
#include "BPMElemental.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"

ABPMDarkKnight::ABPMDarkKnight()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SM(TEXT("SkeletalMesh'/Game/Monsters/DarkKnight/DarkKnight.DarkKnight'"));

	if (SM.Succeeded())
	{
		MeshMonster->SetSkeletalMesh(SM.Object);
	}	
	MeshMonster->SetRelativeLocation(FVector(20.0f, 0.0f, -50.f));
	MeshMonster->SetRelativeScale3D(FVector(2.f, 2.f, 2.f));

	
}

void ABPMDarkKnight::BeginPlay()
{
	Super::BeginPlay();

	MaxHP = 3000;
	CurHP = MaxHP;
	MoveSpeed = 300.f;
	
	IsWalkingLeft = true;
}

void ABPMDarkKnight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (IsDead)
		return;
	

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	FVector PlayerLocation = PlayerPawn->GetActorLocation();
	FVector MonsterLocation = GetActorLocation();
	FVector Direction = PlayerLocation - MonsterLocation;
	FVector NormalDirection = Direction;
	NormalDirection.Normalize();
	
	SetActorRotation(NormalDirection.Rotation());

	if(IsWalking)
	{
		
		if(WalkTime == 0.f)
		{
			if(IsWalkingLeft)
			{
				AnimInstance->PlayDarkKinightWalkLeftMonatage();
			}
			else if(IsWalkingRight)
			{
				AnimInstance->PlayDarkKinightWalkRightMonatage();				
			}
		}
		
		FVector HorizontalDirection = NormalDirection;
		HorizontalDirection = FRotator(0, 90, 0).RotateVector(HorizontalDirection);
		HorizontalDirection.Z = 0.f;

		if(IsWalkingLeft)
		{
			GetCharacterMovement()->MoveSmooth((HorizontalDirection * -MoveSpeed), DeltaTime);
		}
		else if(IsWalkingRight)
		{
			GetCharacterMovement()->MoveSmooth((HorizontalDirection * MoveSpeed), DeltaTime);
		}

		WalkTime += DeltaTime;

		if(WalkTime >= 2.f)
		{
			WalkTime = 0.f;
			IsWalking = false;
			
			if(IsWalkingLeft)
			{
				IsWalkingLeft = false;
				IsWalkingRight = true;
			}
			else if(IsWalkingRight)
			{
				IsWalkingLeft = true;
				IsWalkingRight = false;				
			}
			
			AnimInstance->Montage_Stop(0.2f);
		}
	}

	if(CurHP <= 0)
	{
		IsDead = true;
	}
}

void ABPMDarkKnight::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ABPMDarkKnight::Attack1()
{
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	FVector PlayerLocation = PlayerPawn->GetActorLocation();
	FVector MonsterLocation = GetActorLocation() + FVector(0.f, 0.f, 100.f);
	FVector Direction = PlayerLocation - MonsterLocation;
	FVector NormalDirection = Direction;
	NormalDirection.Normalize();
	
	if (ProjectileClass != nullptr)
	{
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	
			ABPMProjectile* projectile = World->SpawnActor<ABPMProjectile>(ProjectileClass, GetActorLocation() + FVector(0.f, 0.f, 100.f), NormalDirection.Rotation(), ActorSpawnParams);
			projectile->SetProjectileOwner(this);
		}
	}
	
	/*if (AnimInstance)
	{
		AnimInstance->PlayDarkKinightAttack1Monatage();
	}*/
}

void ABPMDarkKnight::Attack2()
{
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	FVector PlayerLocation = PlayerPawn->GetActorLocation();
	FVector MonsterLocation = GetActorLocation() + FVector(0.f, 0.f, 100.f);
	FVector Direction = PlayerLocation - MonsterLocation;
	FVector NormalDirection = Direction;
	NormalDirection.Normalize();
	
	if (ProjectileClass != nullptr)
	{
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	
			ABPMProjectile* projectile = World->SpawnActor<ABPMProjectile>(ProjectileClass, GetActorLocation() + FVector(0.f, 0.f, 100.f), NormalDirection.Rotation(), ActorSpawnParams);
			projectile->SetProjectileOwner(this);
			
			ABPMProjectile* projectile2 = World->SpawnActor<ABPMProjectile>(ProjectileClass, GetActorLocation() + FVector(0.f, 0.f, 100.f), NormalDirection.Rotation() - FRotator(0.f, 15.f, 0.f), ActorSpawnParams);
			projectile2->SetProjectileOwner(this);
			
			ABPMProjectile* projectile3 = World->SpawnActor<ABPMProjectile>(ProjectileClass, GetActorLocation() + FVector(0.f, 0.f, 100.f), NormalDirection.Rotation() - FRotator(0.f, -15.f, 0.f), ActorSpawnParams);
			projectile3->SetProjectileOwner(this);
		}
	}
	
	/*if (AnimInstance)
	{
		AnimInstance->PlayDarkKinightAttack2Monatage();
	}*/
}

void ABPMDarkKnight::SpawnMonster()
{
	// 기본애니메이션 변경, 인터벌 줘서 세번 연속 생성, 다시 기본애니메이션 변경
	if (ElementalClass != nullptr)
	{
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	
			float rand = FMath::RandRange(-200.f, 200.f);
			ABPMElemental* Elemental = World->SpawnActor<ABPMElemental>(ElementalClass, GetActorLocation() + FVector(0.f, rand, 700.f), FRotator::ZeroRotator, ActorSpawnParams);
		}
	}
	
	/*if (AnimInstance)
	{
		AnimInstance->PlayDarkKinightSpawnMonatage();
	}*/
}
