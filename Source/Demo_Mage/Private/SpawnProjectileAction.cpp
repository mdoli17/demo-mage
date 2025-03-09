// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnProjectileAction.h"

#include "DemoCharacterToAnimInterface.h"

void USpawnProjectileAction::Initialize_Implementation()
{
	Super::Initialize_Implementation();

	AnimInterface->GetBasicAttackReadyEvent().AddDynamic(this, &USpawnProjectileAction::USpawnProjectileAction::BasicAttackActionReadyCallback);
	// TODO: Handle un-subscribe in Deinitialize (When it is implemented)
}

bool USpawnProjectileAction::StartActionImplementation_Implementation(const FActionParams& Params)
{
	AnimInterface->StartBasicAttack();
	return Super::StartActionImplementation_Implementation(Params);
}

bool USpawnProjectileAction::StopActionImplementation_Implementation()
{
	AnimInterface->StopBasicAttack();
	return Super::StopActionImplementation_Implementation();
}

void USpawnProjectileAction::BasicAttackActionReadyCallback()
{
	FHitResult HitResult;
	FVector ActorEyeViewPointLocation;
	FRotator ActorEyeViewPointRotation;
	DemoCharacter->GetActorEyesViewPoint(ActorEyeViewPointLocation, ActorEyeViewPointRotation);

	const FVector LineStart = ActorEyeViewPointLocation;
	const FVector LineEnd = LineStart + ActorEyeViewPointRotation.Vector() * 100000.0f;
	GetWorld()->LineTraceSingleByChannel(HitResult, LineStart, LineEnd, ECC_Visibility);

	const FVector ProjectileDestination = HitResult.bBlockingHit ? HitResult.Location : LineEnd;

	DrawDebugLine(GetWorld(), LineStart, ProjectileDestination, HitResult.bBlockingHit ? FColor::Green : FColor::Orange, false, 5.0f);

	const FVector SpawnPoint = AnimInterface->GetProjectileSpawnLocation();
	const FRotator SpawnRotator = FRotator::ZeroRotator;
	const FVector ProjectileDirection = (ProjectileDestination - SpawnPoint).GetSafeNormal();
	const FActorSpawnParameters Parameters;

	ADemoProjectile* Projectile = GetWorld()->SpawnActor<ADemoProjectile>(ProjectileClass, SpawnPoint, SpawnRotator, Parameters);
	if (Projectile)
	{
		Projectile->Setup(Owner);
		Projectile->Launch(ProjectileDirection);
	}

	UE_LOG(LogTemp, Log, TEXT("Called Basic Attack Action Ready Callback"));
}
