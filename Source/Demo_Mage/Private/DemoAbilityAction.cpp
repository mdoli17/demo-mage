// Fill out your copyright notice in the Description page of Project Settings.


#include "DemoAbilityAction.h"

void UDemoAbilityAction::Initialize_Implementation()
{
	AnimInterface = Cast<IDemoCharacterToAnimInterface>(DemoCharacter->GetSkeletalMesh()->GetAnimInstance());
	ensure(AnimInterface);
	Super::Initialize_Implementation();
}

UDemoAbilityComponent* UDemoAbilityAction::GetOwningComponent() const
{
	return Cast<UDemoAbilityComponent>(GetOuter());
}
