// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectAbilityAction.h"

#include "DemoCharacterToAnimInterface.h"

bool USelectAbilityAction::ExecuteActionImplementation_Implementation(const FActionParams& Params)
{
	UDemoAbilityComponent* DemoAbilityComponent = Cast<UDemoAbilityComponent>(GetOwningComponent());
	const ECharacterAbilityType AbilityType = static_cast<ECharacterAbilityType>(Params.IntValue);
	DemoAbilityComponent->SelectAbility(AbilityType);
	Cast<IDemoCharacterToAnimInterface>(DemoCharacter->GetSkeletalMesh()->GetAnimInstance())->SetAbilityType(AbilityType);

	return true;
}
