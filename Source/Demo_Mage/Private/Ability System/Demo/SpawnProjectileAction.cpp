// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability System/Demo/SpawnProjectileAction.h"

#include "Characters/Animations/DemoCharacterToAnimInterface.h"

void USpawnProjectileAction::Initialize_Implementation()
{
	Super::Initialize_Implementation();

	AnimInterface->GetAnimNotifyEventReceived().AddDynamic(this, &USpawnProjectileAction::AnimNotifyEventReceivedHandler);
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

void USpawnProjectileAction::LaunchProjectile()
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
	FActorSpawnParameters Parameters;
	Parameters.Instigator = DemoCharacter;

	if (ADemoProjectile* Projectile = GetWorld()->SpawnActor<ADemoProjectile>(ProjectileClass, SpawnPoint, SpawnRotator, Parameters))
	{
		Projectile->Launch(ProjectileDirection);
	}

	OnSpawnCalled();
}

void USpawnProjectileAction::AnimNotifyEventReceivedHandler(const FAnimNotifyEvent& AnimNotifyEvent)
{
	if (AnimNotifyEvent.NotifyName != AnimNotifyName) return;

	LaunchProjectile();
}
