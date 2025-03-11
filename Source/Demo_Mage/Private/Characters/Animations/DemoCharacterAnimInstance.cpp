// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Animations/DemoCharacterAnimInstance.h"

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

	// TODO: Maybe it will be better to implement Custom Notifies, and broadcast events or call direct functions of actions from there.
	OnAnimNotifyEventReceived.Broadcast(AnimNotifyEvent);

	return Super::HandleNotify(AnimNotifyEvent);
}
