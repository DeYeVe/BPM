// Copyright Epic Games, Inc. All Rights Reserved.

#include "BPMProjectile.h"

#include "BPMCharacter.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"

ABPMProjectile::ABPMProjectile() 
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &ABPMProjectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 800.f;
	ProjectileMovement->MaxSpeed = 800.f;
	ProjectileMovement->ProjectileGravityScale = 0.f;

	// Die after 3 seconds by default
	InitialLifeSpan = 20.0f;
}

void ABPMProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) )//&& OtherComp->IsSimulatingPhysics())
	{
		if(OtherActor->IsA(ABPMCharacter::StaticClass()))
		{
			FDamageEvent DamageEvent;
			Cast<ABPMCharacter>(OtherActor)->TakeDamage(25.f, DamageEvent, ProjectileOwner->GetController(), ProjectileOwner);
			UE_LOG(LogTemp, Log, TEXT("Demon Bat Fire Hit Player"));			
		}
		Destroy();
	}
}

void ABPMProjectile::SetProjectileOwner(ABPMMonster* TargetProjectileOwner)
{
	ProjectileOwner = TargetProjectileOwner;
}
