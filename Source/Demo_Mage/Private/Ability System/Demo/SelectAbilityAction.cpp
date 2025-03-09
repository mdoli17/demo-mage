// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability System/Demo/SelectAbilityAction.h"

#include "Characters/Animations/DemoCharacterToAnimInterface.h"

bool USelectAbilityAction::ExecuteActionImplementation_Implementation(const FActionParams& Params)
{
	UDemoAbilityComponent* DemoAbilityComponent = GetOwningComponent();
	const ECharacterAbilityType AbilityType = static_cast<ECharacterAbilityType>(Params.IntValue);
	DemoAbilityComponent->SelectAbility(AbilityType);

	AnimInterface->SetAbilityType(AbilityType);

	return true;
}
