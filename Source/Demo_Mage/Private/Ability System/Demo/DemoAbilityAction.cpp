// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability System/Demo/DemoAbilityAction.h"

void UDemoAbilityAction::Initialize(AActor* Instigator)
{
	DemoCharacter = Cast<ADemoCharacter>(Instigator);
	AnimInterface = Cast<IDemoCharacterToAnimInterface>(DemoCharacter->GetSkeletalMesh()->GetAnimInstance());
	Super::Initialize(Instigator);
}

void UDemoAbilityAction::Initialize_Implementation()
{
	ensure(AnimInterface);
	Super::Initialize_Implementation();
}

UDemoAbilityComponent* UDemoAbilityAction::GetOwningComponent() const
{
	return Cast<UDemoAbilityComponent>(GetOuter());
}
