// Copyright Epic Games, Inc. All Rights Reserved.

#include "BPMCharacter.h"
#include "BPMProjectile.h"
#include "BPMAnimInstance.h"
#include "BPMGameMode.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "BPMTimerActor.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"
#include "BPMHUDWidget.h"


//////////////////////////////////////////////////////////////////////////
// ABPMCharacter

ABPMCharacter::ABPMCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
	GetCapsuleComponent()->SetCollisionProfileName("Player");

	// set our turn rates for input
	TurnRateGamepad = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeRotation(FRotator(0.f, -90.f, 90.f));
	Mesh1P->SetRelativeLocation(FVector(-15.0f, -0.0f, -140.f));
 
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SM(TEXT("SkeletalMesh'/Game/Player/FP_player/Player.Player_FP_player_mo'"));

	if (SM.Succeeded())
	{
		GetMesh1P()->SetSkeletalMesh(SM.Object);
	}
	
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SW(TEXT("SkeletalMesh'/Game/Weapons/Pistol/BA_pistol.BA_pistol_BA_pistol_mo'"));
	if(SW.Succeeded())
	{
		WeaponMesh->SetSkeletalMesh(SW.Object);
	}
	
	FName WeaponSocket(TEXT("weapon_R292_socket"));
	
	if(GetMesh1P()->DoesSocketExist(WeaponSocket))
	{
		UE_LOG(LogTemp, Log, TEXT("weapon socket"));
		WeaponMesh->SetupAttachment(GetMesh1P(), WeaponSocket);
	}
	
	WeaponComponent = CreateDefaultSubobject<UTP_WeaponComponent>(TEXT("WeaponComp"));

	//sound
	static ConstructorHelpers::FObjectFinder<USoundBase> OffBeatSoundBase(TEXT("SoundWave'/Game/Sounds/SE/OffBeat.OffBeat'"));
	if (OffBeatSoundBase.Succeeded())
	{
		OffBeatSound = OffBeatSoundBase.Object;
	}
	
	static ConstructorHelpers::FObjectFinder<USoundBase> DashSoundBase(TEXT("SoundWave'/Game/Sounds/SE/Dash.Dash'"));
	if (DashSoundBase.Succeeded())
	{
		DashSound = DashSoundBase.Object;
	}

	FootstepAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("FootstepAudioComp"));
	static ConstructorHelpers::FObjectFinder<USoundBase> FootstepSoundBase(TEXT("SoundWave'/Game/Sounds/SE/Footstep.Footstep'"));
	if (FootstepSoundBase.Succeeded())
	{
		FootstepSound = FootstepSoundBase.Object;
		FootstepAudioComponent->SetSound(FootstepSound);
	}

	static ConstructorHelpers::FObjectFinder<USoundBase> NoAmmoSoundBase(TEXT("SoundWave'/Game/Sounds/SE/NoAmmo.NoAmmo'"));
	if (NoAmmoSoundBase.Succeeded())
	{
		NoAmmoSound = NoAmmoSoundBase.Object;
	}
	
	static ConstructorHelpers::FObjectFinder<USoundBase> HitSoundBase(TEXT("SoundWave'/Game/Sounds/SE/Hit.Hit'"));
	if (HitSoundBase.Succeeded())
	{
		HitSound = HitSoundBase.Object;
	}

	//stat
	MaxHP = 100;
	CurHP = MaxHP;
}

void ABPMCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
	
	AnimInstance = Cast<UBPMAnimInstance>(GetMesh1P()->GetAnimInstance());
	WeaponComponent->AttachWeapon(this);

	TimerActor = Cast<ABPMTimerActor>(UGameplayStatics::GetActorOfClass(GetWorld(), ABPMTimerActor::StaticClass()));

	GameMode = Cast<ABPMGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	HUDWidget = Cast<UBPMHUDWidget>(GameMode->CurWidget);
}

void ABPMCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void ABPMCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// condition check
	if (TimerActor->IsInCrotchet() && !bIsInCrotchet)
	{
		bIsInCrotchet = true;
		bCanAct = true;
		//UE_LOG(LogTemp, Log, TEXT("Change to c"));
		if(DashInterval > 0)
			DashInterval--;
	}
	
	if (TimerActor->IsInQuaver() && bIsInCrotchet)
	{
		bIsInCrotchet = false;
		bCanAct = true;
		//UE_LOG(LogTemp, Log, TEXT("Change to q"));
		if(DashInterval > 0)
			DashInterval--;
	}

	if (bIsDashing)
	{
		DashTimeRemaining -= DeltaTime;
		FVector DashDirection = GetCharacterMovement()->GetLastInputVector();
		
		GetCharacterMovement()->MoveSmooth(DashDirection * DashSpeed, DeltaTime);
		
		if(DashTimeRemaining <= 0.f)
		{
			DashEnd();
		}
	}

	if (GetCharacterMovement()->Velocity.Size() > 0.f && !bIsDashing && !(GetCharacterMovement()->IsFalling()))
	{
		if (!FootstepAudioComponent->IsPlaying())
			FootstepAudioComponent->Play();
	}
	else
	{
		FootstepAudioComponent->Stop();
	}

	// UI
	if (GameMode)
	{
		if (HUDWidget)
		{
			
			HUDWidget->SetCurAmmo(FString::Printf(TEXT("%1d"), WeaponComponent->GetCurAmmo()));
			HUDWidget->SetMaxAmmo(FString::Printf(TEXT("%1d"), WeaponComponent->GetMaxAmmo()));
			HUDWidget->SetCurHP(FString::Printf(TEXT("%3d"), CurHP));
			HUDWidget->SetMaxHP(FString::Printf(TEXT("%3d"), MaxHP));
			HUDWidget->SetCoin(FString::Printf(TEXT("%2d"), Coin));
		}
	}

	// gain coins
	TArray<AActor*> OverlappingActors;
	GetCapsuleComponent()->GetOverlappingActors(OverlappingActors);
	for (AActor* Actor : OverlappingActors)
	{
		if (Actor->ActorHasTag(TEXT("Coin")))
		{
			Coin++;
			Actor->Destroy();
		}			
	}		
}

//////////////////////////////////////////////////////////////////////////// Input

void ABPMCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Bind fire event
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ABPMCharacter::Fire);
	
	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &ABPMCharacter::ReloadStart);
	
	// // Enable touchscreen input
	// EnableTouchscreenMovement(PlayerInputComponent);

	// Bind movement events
	PlayerInputComponent->BindAxis("Move Forward / Backward", this, &ABPMCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &ABPMCharacter::MoveRight);

	PlayerInputComponent->BindAction("Dash Start", IE_Pressed, this, &ABPMCharacter::DashStart);
	PlayerInputComponent->BindAction("Dash End", IE_Released, this, &ABPMCharacter::DashEnd);
	
	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "Mouse" versions handle devices that provide an absolute delta, such as a mouse.
	// "Gamepad" versions are for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn Right / Left Mouse", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Look Up / Down Mouse", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn Right / Left Gamepad", this, &ABPMCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("Look Up / Down Gamepad", this, &ABPMCharacter::LookUpAtRate);
}

/*
void ABPMCharacter::OnPrimaryAction()
{
	// Trigger the OnItemUsed Event
	OnUseItem.Broadcast();
}

void ABPMCharacter::BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if (TouchItem.bIsPressed == true)
	{
		return;
	}
	if ((FingerIndex == TouchItem.FingerIndex) && (TouchItem.bMoved == false))
	{
		OnPrimaryAction();
	}
	TouchItem.bIsPressed = true;
	TouchItem.FingerIndex = FingerIndex;
	TouchItem.Location = Location;
	TouchItem.bMoved = false;
}

void ABPMCharacter::EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if (TouchItem.bIsPressed == false)
	{
		return;
	}
	TouchItem.bIsPressed = false;
}*/

void ABPMCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void ABPMCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void ABPMCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void ABPMCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

/*
bool ABPMCharacter::EnableTouchscreenMovement(class UInputComponent* PlayerInputComponent)
{
	if (FPlatformMisc::SupportsTouchInput() || GetDefault<UInputSettings>()->bUseMouseForTouch)
	{
		PlayerInputComponent->BindTouch(EInputEvent::IE_Pressed, this, &ABPMCharacter::BeginTouch);
		PlayerInputComponent->BindTouch(EInputEvent::IE_Released, this, &ABPMCharacter::EndTouch);

		return true;
	}
	
	return false;
}*/

void ABPMCharacter::Fire()
{
	if (!bCanAct)
	{		
		PlayOffBeat();
		
		return;
	}
	if(TimerActor)
		UE_LOG(LogTemp, Log, TEXT("Has tiactor"));
	if (!TimerActor->IsInCrotchet() && !TimerActor->IsInQuaver())
	{		
		PlayOffBeat();

		return;
	}

	if (WeaponComponent->GetCurAmmo() == 0)
	{
		NoAmmo();
		return;
	}
	
	UE_LOG(LogTemp, Log, TEXT("Fire"));

	if (AnimInstance)
	{
		AnimInstance->PlayPlayerFireMontage();
		Cast<UBPMAnimInstance>(WeaponMesh->GetAnimInstance())->PlayPistolFireMontage();
	}
	//OnUseItem.Broadcast();
	WeaponComponent->Fire();
		
	bCanAct = false;
	bISReloading = false;

}

void ABPMCharacter::DashStart()
{
	if (!bCanAct || bIsDashing || DashInterval != 0)
	{
		PlayOffBeat();

		return;
	}

	if (!TimerActor->IsInCrotchet() && !TimerActor->IsInQuaver())
	{		
		PlayOffBeat();

		return;
	}

	if (DashSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, DashSound, GetActorLocation());
	}

	bIsDashing = true;
	bCanAct = false;
	GetCharacterMovement()->GravityScale = 0.f;
	DashTimeRemaining = DashDuration;
	DashInterval = 2;
}

void ABPMCharacter::DashEnd()
{
	bIsDashing = false;
	DashTimeRemaining = 0.f;
	GetCharacterMovement()->GravityScale = 1.f;
}

void ABPMCharacter::ReloadStart()
{
	if (!bCanAct)
	{		
		PlayOffBeat();
		
		return;
	}

	if (!TimerActor->IsInCrotchet() && !TimerActor->IsInQuaver())
	{		
		PlayOffBeat();

		return;
	}

	if (bISReloading)
	{
		ReloadEnd();
		
		return;
	}
	
	if (AnimInstance)
	{
		AnimInstance->PlayPlayerReloadStartMontage();
		Cast<UBPMAnimInstance>(WeaponMesh->GetAnimInstance())->PlayPistolReloadStartMontage();
	}
	
	bISReloading = true;
	bCanAct = false;
	WeaponComponent->ReloadStart();
}

void ABPMCharacter::ReloadEnd()
{		
	if (AnimInstance)
	{
		AnimInstance->PlayPlayerReloadEndMontage();
		Cast<UBPMAnimInstance>(WeaponMesh->GetAnimInstance())->PlayPistolReloadEndMontage();
	}
	
	bISReloading = false;
	bCanAct = false;
	WeaponComponent->ReloadEnd();
}

void ABPMCharacter::NoAmmo()
{
	if (NoAmmoSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, NoAmmoSound, GetActorLocation());
	}
}

void ABPMCharacter::PlayOffBeat()
{
	if (OffBeatSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, OffBeatSound, GetActorLocation());
	}
}

float ABPMCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	if (HitSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
	}

	if(HUDWidget)
		HUDWidget->OnPlayerHit();
	
	CurHP -= DamageAmount;
	
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}
