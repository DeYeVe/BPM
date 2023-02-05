// Copyright Epic Games, Inc. All Rights Reserved.


#include "TP_WeaponComponent.h"
#include "BPMCharacter.h"
#include "BPMProjectile.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PlayerController.h"
#include "Camera/PlayerCameraManager.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"

// Sets default values for this component's properties
UTP_WeaponComponent::UTP_WeaponComponent()
{
	// Default offset from the character location for projectiles to spawn
	MuzzleOffset = FVector(100.0f, 0.0f, 10.0f);

	static ConstructorHelpers::FObjectFinder<USoundBase> FireSoundBase(TEXT("SoundWave'/Game/Sounds/SE/PistolFire.PistolFire'"));
	if (FireSoundBase.Succeeded())
	{
		FireSound = FireSoundBase.Object;
	}
	
	static ConstructorHelpers::FObjectFinder<USoundBase> ReloadStartSoundBase(TEXT("SoundWave'/Game/Sounds/SE/PistolReloadStart.PistolReloadStart'"));
	if (ReloadStartSoundBase.Succeeded())
	{
		ReloadStartSound = ReloadStartSoundBase.Object;
	}
	
	static ConstructorHelpers::FObjectFinder<USoundBase> ReloadEndSoundBase(TEXT("SoundWave'/Game/Sounds/SE/PistolReloadEnd.PistolReloadEnd'"));
	if (ReloadEndSoundBase.Succeeded())
	{
		ReloadEndSound = ReloadEndSoundBase.Object;
	}
	
	static ConstructorHelpers::FObjectFinder<UParticleSystem> MuzzleObj (TEXT("ParticleSystem'/Game/ParagonDrongo/FX/Particles/Abilities/Primary/FX/P_Drongo_Primary_MuzzleFlash.P_Drongo_Primary_MuzzleFlash'"));
	if (MuzzleObj.Succeeded())
	{
		MuzzleEffect = MuzzleObj.Object;
	}

	MaxAmmo = 8;
	CurrentAmmo = MaxAmmo;
}


void UTP_WeaponComponent::Fire()
{
	if(Character == nullptr)
	//if(Character == nullptr || Character->GetController() == nullptr)
	{
		return;
	}

	CurrentAmmo--;
	UE_LOG(LogTemp, Log, TEXT("%d"), CurrentAmmo);
	
	// scan hit using trace
	{
		FHitResult HitResult;
		FCollisionQueryParams Params(NAME_None, false, Character);
		TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes; // 히트 가능한 오브젝트 유형들.
		TEnumAsByte<EObjectTypeQuery> WorldStatic = UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic);
		TEnumAsByte<EObjectTypeQuery> WorldDynamic = UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldDynamic);
		FVector StartLocation = Character->GetFirstPersonCameraComponent()->GetComponentLocation();
		FVector EndLocation = Character->GetFirstPersonCameraComponent()->GetComponentLocation()
			+ Character->GetFirstPersonCameraComponent()->GetForwardVector() * 1200;

		bool IsHitResult = GetWorld()->LineTraceSingleByObjectType(
			HitResult,
			StartLocation,
			EndLocation,
			ObjectTypes,
			Params);

		//debugline
		if (true)
		{
			FColor DrawColor = IsHitResult ? FColor::Green : FColor::Red;
			const float DebugLifeTime = 5.0f;
			DrawDebugLine(GetWorld(), StartLocation, EndLocation, DrawColor, false, DebugLifeTime);
		}

		if (IsHitResult)
		{
			UE_LOG(LogTemp, Log, TEXT("Hit"));
		}
		else
		{
			
		}
	}
	
	if (MuzzleEffect != nullptr)
	{
		//UE_LOG(LogTemp, Log, TEXT("has muzzlefx"));
		GameStatic->SpawnEmitterAttached(MuzzleEffect, Character->GetWeaponMesh(), FName("Muzzle"),
			FVector(ForceInit), FRotator::ZeroRotator, FVector(0.005));
	}
	
	/*
	// Try and fire a projectile
	if (ProjectileClass != nullptr)
	{
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			// APlayerController* PlayerController = Cast<APlayerController>(Character->GetController());
			// const FRotator SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();
			
			APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
			const FRotator SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();
			UE_LOG(LogTemp, Log, TEXT("%f %f %f"), SpawnRotation.Vector().X, SpawnRotation.Vector().Y, SpawnRotation.Vector().Z);

			// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
			const FVector SpawnLocation = GetOwner()->GetActorLocation() + SpawnRotation.RotateVector(MuzzleOffset);
			
			//Set Spawn Collision Handling Override
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	
			// Spawn the projectile at the muzzle
			World->SpawnActor<ABPMProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);

			if (MuzzleEffect != nullptr)
			{
				UE_LOG(LogTemp, Log, TEXT("has muzzlefx"));
				GameStatic->SpawnEmitterAttached(MuzzleEffect, WeaponMesh, FName("Muzzle"),
					FVector(ForceInit), FRotator::ZeroRotator, FVector(0.005));
			}
		}
	}*/
	
	// Try and play the sound if specified
	if (FireSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, Character->GetActorLocation());
	}
	
	// Try and play a firing animation if specified
	if (FireAnimation != nullptr)
	{
		// Get the animation object for the arms mesh
		UAnimInstance* PlayerAnimInstance = Character->GetMesh1P()->GetAnimInstance();
		if (PlayerAnimInstance != nullptr)
		{
			PlayerAnimInstance->Montage_Play(FireAnimation, 1.f);
		}
	}
}

void UTP_WeaponComponent::ReloadStart()
{
	if (ReloadStartSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, ReloadStartSound, Character->GetActorLocation());
	}

	if (ReloadStartAnimation != nullptr)
	{
		// Get the animation object for the arms mesh
		UAnimInstance* PlayerAnimInstance = Character->GetMesh1P()->GetAnimInstance();
		if (PlayerAnimInstance != nullptr)
		{
			PlayerAnimInstance->Montage_Play(ReloadStartAnimation, 1.f);
		}
	}
}

void UTP_WeaponComponent::ReloadEnd()
{
	if (ReloadEndSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, ReloadEndSound, Character->GetActorLocation());
	}

	if (ReloadEndAnimation != nullptr)
	{
		// Get the animation object for the arms mesh
		UAnimInstance* PlayerAnimInstance = Character->GetMesh1P()->GetAnimInstance();
		if (PlayerAnimInstance != nullptr)
		{
			PlayerAnimInstance->Montage_Play(ReloadEndAnimation, 1.f);
		}
	}

	CurrentAmmo = MaxAmmo;
}


void UTP_WeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if(Character != nullptr)
	{
		// Unregister from the OnUseItem Event
		Character->OnUseItem.RemoveDynamic(this, &UTP_WeaponComponent::Fire);
	}
}

void UTP_WeaponComponent::AttachWeapon(ABPMCharacter* TargetCharacter)
{
	Character = TargetCharacter;
	if(Character != nullptr)
	{
		// // Attach the weapon to the First Person Character
		// FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
		// GetOwner()->AttachToComponent(Character->GetMesh1P(),AttachmentRules, FName(TEXT("weapon_R292_socket")));

		// Register so that Fire is called every time the character tries to use the item being held
		Character->OnUseItem.AddDynamic(this, &UTP_WeaponComponent::Fire);
	}
}

