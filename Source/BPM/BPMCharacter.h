// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BPMWeapon.h"
#include "GameFramework/Character.h"
#include "BPMCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class USceneComponent;
class UCameraComponent;
class UAnimMontage;
class USoundBase;

// Declaration of the delegate that will be called when the Primary Action is triggered
// It is declared as dynamic so it can be accessed also in Blueprints
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUseItem);

UCLASS(config=Game)
class ABPMCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleAnywhere, Category=Mesh)
	USkeletalMeshComponent* Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;
	

public:
	ABPMCharacter();

protected:
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


public:
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float TurnRateGamepad;

	/** Delegate to whom anyone can subscribe to receive this event */
	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnUseItem OnUseItem;
protected:
	//
	// /** Fires a projectile. */
	// void OnPrimaryAction();

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles strafing movement, left and right */
	void MoveRight(float Val);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/*struct TouchData
	{
		TouchData() { bIsPressed = false;Location=FVector::ZeroVector;}
		bool bIsPressed;
		ETouchIndex::Type FingerIndex;
		FVector Location;
		bool bMoved;
	};
	void BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location);
	void EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location);
	void TouchUpdate(const ETouchIndex::Type FingerIndex, const FVector Location);
	TouchData	TouchItem;
	*/
	
protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

	// /* 
	//  * Configures input for touchscreen devices if there is a valid touch interface for doing so 
	//  *
	//  * @param	InputComponent	The input component pointer to bind controls to
	//  * @returns true if touch controls were enabled.
	//  */
	// bool EnableTouchscreenMovement(UInputComponent* InputComponent);

public:
	/** Returns Mesh1P subobject **/
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	USkeletalMeshComponent* GetWeaponMesh() const { return WeaponMesh; }
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=Weapon)
	UTP_WeaponComponent* WeaponComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite,Category=Mesh)
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY()
	UBPMAnimInstance* AnimInstance;

	UPROPERTY()
	class ABPMTimerActor* TimerActor;
	
	UPROPERTY()
	class ABPMGameMode* GameMode;

	UPROPERTY()
	class UBPMHUDWidget* HUDWidget;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Sound)
	USoundBase* OffBeatSound;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Sound)
	USoundBase* DashSound;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Sound)
	USoundBase* FootstepSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Sound)
	UAudioComponent* FootstepAudioComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Sound)
	USoundBase* NoAmmoSound;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Sound)
	USoundBase* HitSound;

private:
	UPROPERTY()
	bool bCanAct = true;

	UPROPERTY()
	bool bIsInCrotchet = false;

	UPROPERTY()
	bool bIsDashing = false;

	UPROPERTY()
	int DashInterval = 0;
	
	UPROPERTY()
	float DashSpeed = 2000.f;

	UPROPERTY()
	float DashDuration = 0.3f;

	UPROPERTY()
	float DashTimeRemaining = 0.f;

	UPROPERTY()
	bool bISReloading = false;

	UPROPERTY()
	int CurHP;
	
	UPROPERTY()
	int MaxHP;
	
	UPROPERTY()
	int Coin;

	UPROPERTY()
	FName InteractingItem;

public:
	UFUNCTION()
	void Fire();

	UFUNCTION()
	void DashStart();	

	UFUNCTION()
	void DashEnd();
	
	UFUNCTION()
	void ReloadStart();	

	UFUNCTION()
	void ReloadEnd();
	
	UFUNCTION()
	void NoAmmo();

	UFUNCTION()
	void PlayOffBeat();
	
	UFUNCTION()
	void Purchase();
	
	UFUNCTION()
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	
};