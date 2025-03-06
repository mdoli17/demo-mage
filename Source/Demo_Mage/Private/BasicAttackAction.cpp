// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicAttackAction.h"

#include "DemoCharacterToAnimInterface.h"

void UBasicAttackAction::Initialize_Implementation()
{
	AnimInterface = Cast<IDemoCharacterToAnimInterface>(DemoCharacter->GetSkeletalMesh()->GetAnimInstance());
	AnimInterface->GetBasicAttackReadyEvent().AddDynamic(this, &UBasicAttackAction::UBasicAttackAction::BasicAttackActionReadyCallback);
	// TODO: Handle un-subscribe in Deinitialize (When it is implemented)
	Super::Initialize_Implementation();
}

bool UBasicAttackAction::StartActionImplementation_Implementation(const FActionParams& Params)
{
	AnimInterface->StartBasicAttack();
	return Super::StartActionImplementation_Implementation(Params);
}

bool UBasicAttackAction::StopActionImplementation_Implementation()
{
	AnimInterface->StopBasicAttack();
	return Super::StopActionImplementation_Implementation();
}

void UBasicAttackAction::BasicAttackActionReadyCallback()
{
	FHitResult HitResult;
	const FVector LineStart = DemoCharacter->GetCamera()->GetComponentLocation();
	const FVector LineEnd = LineStart + DemoCharacter->GetCamera()->GetForwardVector() * 100000.0f;
	GetWorld()->LineTraceSingleByChannel(HitResult, LineStart, LineEnd, ECC_Visibility);

	const FVector ProjectileDestination = HitResult.bBlockingHit ? HitResult.Location : LineEnd;

	DrawDebugLine(GetWorld(), LineStart, ProjectileDestination, HitResult.bBlockingHit ? FColor::Green : FColor::Orange, false, 5.0f);

	const FVector SpawnPoint = AnimInterface->GetProjectileSpawnLocation();
	const FRotator SpawnRotator = FRotator::ZeroRotator;
	const FVector ProjectileDirection = (ProjectileDestination - SpawnPoint).GetSafeNormal();
	const FActorSpawnParameters Parameters;

	const ADemoProjectile* Projectile = GetWorld()->SpawnActor<ADemoProjectile>(ProjectileClass, SpawnPoint, SpawnRotator, Parameters);
	if (Projectile)
	{
		Projectile->Launch(ProjectileDirection);
	}

	UE_LOG(LogTemp, Log, TEXT("Called Basic Attack Action Ready Callback"));
}
