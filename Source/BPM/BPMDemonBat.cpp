// Fill out your copyright notice in the Description page of Project Settings.


#include "BPMDemonBat.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "BPMProjectile.h"

// Sets default values
ABPMDemonBat::ABPMDemonBat()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SM(TEXT("SkeletalMesh'/Game/Monsters/DemonBat/SK_DemonBat.SK_DemonBat'"));

	if (SM.Succeeded())
	{
		MeshMonster->SetSkeletalMesh(SM.Object);
	}	
	MeshMonster->SetRelativeLocation(FVector(20.0f, 0.0f, -50.f));
	MeshMonster->SetRelativeScale3D(FVector(0.9f, 0.9f, 0.9f));

	MaxHP = 50;
	CurHP = MaxHP;
	MoveSpeed = 300.f;
	MoveIntervalTime = 4.f;
	AttackCoolDown = 1.5f;
}

// Called when the game starts or when spawned
void ABPMDemonBat::BeginPlay()
{
	Super::BeginPlay();
	
	GetCharacterMovement()->GravityScale = 0.f;
}

// Called every frame
void ABPMDemonBat::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// behavior, move & attck
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	FVector PlayerLocation = PlayerPawn->GetActorLocation();
	FVector MonsterLocation = GetActorLocation();
	FVector Direction = PlayerLocation - MonsterLocation;
	FVector NormalDirection = Direction;
	NormalDirection.Normalize();
	
	// attack
	AttackCoolDown -= DeltaTime;
	if (AttackCoolDown <= 0.f)
	{
		AttackCoolDown = 1.5f;
		
		if (ProjectileClass != nullptr)
		{
			UWorld* const World = GetWorld();
			if (World != nullptr)
			{
				FActorSpawnParameters ActorSpawnParams;
				ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	
				World->SpawnActor<ABPMProjectile>(ProjectileClass, GetActorLocation(), NormalDirection.Rotation(), ActorSpawnParams);
			}
		}
	}
		
	// move
	SetActorRotation(NormalDirection.Rotation());

	FVector HorizontalDirection = NormalDirection;
	HorizontalDirection = FRotator(0, 90, 0).RotateVector(HorizontalDirection);
	HorizontalDirection.Z = 0.f;
	
	MoveIntervalTime -= DeltaTime;
	if (MoveIntervalTime <= 0.f)
	{
		MoveIntervalTime = 4.f;
	}
	else if (MoveIntervalTime > 2.f)
	{
		GetCharacterMovement()->MoveSmooth((HorizontalDirection * MoveSpeed), DeltaTime);
	}
	else // <= 2.f
	{
		GetCharacterMovement()->MoveSmooth((HorizontalDirection * - MoveSpeed), DeltaTime);
	}
	
	if (Direction.Size() > 1200.f)
	{
		NormalDirection.Z = 0.f;
		GetCharacterMovement()->MoveSmooth((NormalDirection * MoveSpeed), DeltaTime);
	}	
}

// Called to bind functionality to input
void ABPMDemonBat::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

