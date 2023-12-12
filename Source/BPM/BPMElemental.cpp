// Fill out your copyright notice in the Description page of Project Settings.


#include "BPMElemental.h"

#include "BPMCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/DamageEvents.h"

// Sets default values
ABPMElemental::ABPMElemental()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SM(TEXT("SkeletalMesh'/Game/Monsters/Elemental/Elemental.Elemental'"));

	if (SM.Succeeded())
	{
		MeshMonster->SetSkeletalMesh(SM.Object);
	}	
	MeshMonster->SetRelativeLocation(FVector(20.0f, 0.0f, -50.f));
	MeshMonster->SetRelativeScale3D(FVector(0.9f, 0.9f, 0.9f));

	MaxHP = 50;
	CurHP = MaxHP;
	MoveSpeed = 300.f;
}

// Called when the game starts or when spawned
void ABPMElemental::BeginPlay()
{
	CurrentLevelName = TEXT("Room5");
	
	Super::BeginPlay();
	
	GetCharacterMovement()->GravityScale = 0.f;
}

// Called every frame
void ABPMElemental::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// behavior, move & attck
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	FVector PlayerLocation = PlayerPawn->GetActorLocation();
	FVector MonsterLocation = GetActorLocation();
	FVector Direction = PlayerLocation - MonsterLocation;
	FVector NormalDirection = Direction;
	NormalDirection.Normalize();
		
	// move
	SetActorRotation(NormalDirection.Rotation());

	FVector HorizontalDirection = NormalDirection;
	HorizontalDirection = FRotator(0, 90, 0).RotateVector(HorizontalDirection);
	HorizontalDirection.Z = 0.f;

	if (Direction.Size() > 150.f)
	{
		if(MonsterLocation.Z <= 400)
			NormalDirection.Z = 0.f;
		GetCharacterMovement()->MoveSmooth((NormalDirection * MoveSpeed), DeltaTime);
	}
	else
	{
		FHitResult HitResult;
		FCollisionQueryParams Params(NAME_None, false, this);

		float AttackRange = 150.f;
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

		Destroy();
	}
}

// Called to bind functionality to input
void ABPMElemental::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
