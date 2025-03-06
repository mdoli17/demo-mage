// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilityAction.h"
#include "DemoCharacterToAnimInterface.h"
#include "DemoCharacterAbilityAction.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_MAGE_API UDemoCharacterAbilityAction : public UAbilityAction
{
	GENERATED_BODY()

public:
	virtual void Initialize_Implementation() override;
	virtual bool StartActionImplementation_Implementation(const FActionParams& Params) override;
	virtual bool StopActionImplementation_Implementation() override;

private:
	IDemoCharacterToAnimInterface* CharacterToAnimInterface;
};
