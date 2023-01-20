// Copyright Epic Games, Inc. All Rights Reserved.

#include "BPMCharacter.h"
#include "BPMProjectile.h"
#include "BPMAnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "BPMTimerActor.h"
#include "Kismet/GameplayStatics.h"


//////////////////////////////////////////////////////////////////////////
// ABPMCharacter

ABPMCharacter::ABPMCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

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

	static ConstructorHelpers::FObjectFinder<USoundBase> FireSoundBase(TEXT("SoundWave'/Game/Sounds/SE/OffBeat.OffBeat'"));
	if (FireSoundBase.Succeeded())
	{
		OffBeatSound = FireSoundBase.Object;
	}

}

void ABPMCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
	
	AnimInstance = Cast<UBPMAnimInstance>(GetMesh1P()->GetAnimInstance());
	WeaponComponent->AttachWeapon(this);

	TimerActor = Cast<ABPMTimerActor>(UGameplayStatics::GetActorOfClass(GetWorld(), ABPMTimerActor::StaticClass()));
}

void ABPMCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void ABPMCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TimerActor->IsInCrotchet() && !IsInCrotchet)
	{
		IsInCrotchet = true;
		CanAct = true;
		UE_LOG(LogTemp, Log, TEXT("Change to c"));
	}
	
	if (TimerActor->IsInQuaver() && IsInCrotchet)
	{
		IsInCrotchet = false;
		CanAct = true;
		UE_LOG(LogTemp, Log, TEXT("Change to q"));
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
	
	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &ABPMCharacter::Reload);
	
	// // Enable touchscreen input
	// EnableTouchscreenMovement(PlayerInputComponent);

	// Bind movement events
	PlayerInputComponent->BindAxis("Move Forward / Backward", this, &ABPMCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &ABPMCharacter::MoveRight);

	PlayerInputComponent->BindAction("Dash", IE_Pressed, this, &ABPMCharacter::Dash);
	
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
	if(!CanAct)
	{
		return;
	}
	
	if(TimerActor->IsInCrotchet() || TimerActor->IsInQuaver())
	{
		UE_LOG(LogTemp, Log, TEXT("Fire"));

		if(AnimInstance)
		{
			AnimInstance->PlayPlayerFireMontage();
			Cast<UBPMAnimInstance>(WeaponMesh->GetAnimInstance())->PlayPistolFireMontage();
		}
		OnUseItem.Broadcast();
		WeaponComponent->Fire();
		
		CanAct = false;
	}
	else
	{		
		if (OffBeatSound != nullptr)
		{
			UE_LOG(LogTemp, Log, TEXT("PlayFireSound"));
			UGameplayStatics::PlaySoundAtLocation(this, OffBeatSound, GetActorLocation());
		}		
	}

}

void ABPMCharacter::Reload()
{
}

void ABPMCharacter::Dash()
{
}
