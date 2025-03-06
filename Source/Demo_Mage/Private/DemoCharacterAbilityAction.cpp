// Fill out your copyright notice in the Description page of Project Settings.


#include "DemoCharacterAbilityAction.h"

void UDemoCharacterAbilityAction::Initialize_Implementation()
{
	Super::Initialize_Implementation();
	CharacterToAnimInterface = Cast<IDemoCharacterToAnimInterface>(DemoCharacter->GetSkeletalMesh()->GetAnimInstance());
}

bool UDemoCharacterAbilityAction::StartActionImplementation_Implementation(const FActionParams& Params)
{
	CharacterToAnimInterface->StartAbility();
	return Super::StartActionImplementation_Implementation(Params);
}

bool UDemoCharacterAbilityAction::StopActionImplementation_Implementation()
{
	CharacterToAnimInterface->StopAbility();
	return Super::StopActionImplementation_Implementation();
}
