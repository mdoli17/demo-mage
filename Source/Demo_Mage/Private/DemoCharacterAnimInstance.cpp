// Fill out your copyright notice in the Description page of Project Settings.


#include "Demo_Mage/Public/DemoCharacterAnimInstance.h"

FVector UDemoCharacterAnimInstance::GetProjectileSpawnLocation()
{
	return GetSkelMeshComponent()->GetSocketLocation(ProjectileSocketName);
}

void UDemoCharacterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (APawn* Pawn = TryGetPawnOwner())
	{
		CharacterInterface = Cast<IDemoCharacterAnimInterface>(Pawn);
	}
}

void UDemoCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (CharacterInterface)
	{
		bIsMoving = CharacterInterface->GetIsMoving();
		bIsSprinting = CharacterInterface->GetIsSprinting();
		bIsInAir = CharacterInterface->GetIsInAir();
	}
}

bool UDemoCharacterAnimInstance::HandleNotify(const FAnimNotifyEvent& AnimNotifyEvent)
{
	UE_LOG(LogTemp, Log, TEXT("Notify Name: %s"), *AnimNotifyEvent.NotifyName.ToString());
	OnBasicAttackReady.Broadcast();
	return Super::HandleNotify(AnimNotifyEvent);
}
