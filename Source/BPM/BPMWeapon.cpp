// Fill out your copyright notice in the Description page of Project Settings.


#include "BPMWeapon.h"
#include "BPMAnimInstance.h"

// Sets default values
ABPMWeapon::ABPMWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SM(TEXT("SkeletalMesh'/Game/Weapons/Pistol/BA_pistol.BA_pistol_BA_pistol_mo'"));
	if(SM.Succeeded())
	{
		WeaponMesh->SetSkeletalMesh(SM.Object);
	}

	WeaponComponent = CreateDefaultSubobject<UTP_WeaponComponent>(TEXT("WeaponComp"));
}

// Called when the game starts or when spawned
void ABPMWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	//AnimInstance = Cast<UBPMAnimInstance>(GetWeaponMesh()->GetAnimInstance());
	
}

// Called every frame
void ABPMWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABPMWeapon::Fire()
{
	if(AnimInstance)
	{
		AnimInstance->PlayPistolFireMontage();
	}

	WeaponComponent->Fire();
}

void ABPMWeapon::Reload()
{
}

