// Fill out your copyright notice in the Description page of Project Settings.


#include "Demo_Mage/Public/DemoCharacterAnimInstance.h"

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
