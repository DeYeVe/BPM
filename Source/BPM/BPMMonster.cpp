// Fill out your copyright notice in the Description page of Project Settings.


#include "BPMMonster.h"

#include "BPMAIController.h"
#include "Components/CapsuleComponent.h"
#include "BPMAnimInstance.h"
#include "BPMItem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABPMMonster::ABPMMonster()
{
	GetCapsuleComponent()->InitCapsuleSize(40.f, 50.0f);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Monster"));
	
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshMonster = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MonsterMesh"));
	MeshMonster->SetupAttachment(GetCapsuleComponent());
	MeshMonster->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	MeshMonster->SetCollisionProfileName(TEXT("Monster"));

	Damage = 25.f;

	//AIControllerClass = ABPMAIController::StaticClass();
	//AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	//BPMAIController = Cast<ABPMAIController>(GetController());

	static ConstructorHelpers::FClassFinder<ABPMItem>BP_Coin(TEXT("Blueprint'/Game/Item/BP_Coin.BP_Coin_C'"));
	if(BP_Coin.Succeeded())
	{
		CoinClass = BP_Coin.Class;
	}
}

// Called when the game starts or when spawned
void ABPMMonster::BeginPlay()
{
	Super::BeginPlay();
	
	AnimInstance = Cast<UBPMAnimInstance>(GetMeshMonster()->GetAnimInstance());
	
	//APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	//BPMAIController->GetBlackboardComponent()->SetValueAsObject(FName(TEXT("Target")), PlayerPawn);
}

// Called every frame
void ABPMMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurHP <= 0)
	{
		//DropItem
		Destroy();
		if(FMath::FRand() >= 0.5f)
			GetWorld()->SpawnActor<ABPMItem>(CoinClass, GetActorLocation(), FRotator(0.f, 0.f, 0.f));
	}

}

// Called to bind functionality to input
void ABPMMonster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float ABPMMonster::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	CurHP -= DamageAmount;
	
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

