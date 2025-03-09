// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectAbilityAction.h"

#include "DemoCharacterToAnimInterface.h"

bool USelectAbilityAction::ExecuteActionImplementation_Implementation(const FActionParams& Params)
{
	UDemoAbilityComponent* DemoAbilityComponent = GetOwningComponent();
	const ECharacterAbilityType AbilityType = static_cast<ECharacterAbilityType>(Params.IntValue);
	DemoAbilityComponent->SelectAbility(AbilityType);

	IDemoCharacterToAnimInterface* AnimInterface = Cast<IDemoCharacterToAnimInterface>(DemoCharacter->GetSkeletalMesh()->GetAnimInstance());
	if (!ensure(AnimInterface)) return false;

	AnimInterface->SetAbilityType(AbilityType);

	return true;
}
