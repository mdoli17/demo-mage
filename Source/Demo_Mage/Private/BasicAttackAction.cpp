// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicAttackAction.h"

#include "DemoCharacterToAnimInterface.h"

void UBasicAttackAction::Initialize_Implementation()
{
	IDemoCharacterToAnimInterface* AnimInterface = Cast<IDemoCharacterToAnimInterface>(DemoCharacter->GetSkeletalMesh()->GetAnimInstance());
	AnimInterface->GetBasicAttackReadyEvent().AddDynamic(this, &UBasicAttackAction::UBasicAttackAction::BasicAttackActionReadyCallback);
	// TODO: Handle un-subscribe in Deinitialize (When it is implemented)
	Super::Initialize_Implementation();
}

bool UBasicAttackAction::StartActionImplementation_Implementation(const FActionParams& Params)
{
	Cast<IDemoCharacterToAnimInterface>(DemoCharacter->GetSkeletalMesh()->GetAnimInstance())->StartBasicAttack();
	return Super::StartActionImplementation_Implementation(Params);
}

bool UBasicAttackAction::StopActionImplementation_Implementation()
{
	Cast<IDemoCharacterToAnimInterface>(DemoCharacter->GetSkeletalMesh()->GetAnimInstance())->StopBasicAttack();
	return Super::StopActionImplementation_Implementation();
}

void UBasicAttackAction::BasicAttackActionReadyCallback()
{
	UE_LOG(LogTemp, Log, TEXT("Called Basic Attack Action Ready Callback"));
}
