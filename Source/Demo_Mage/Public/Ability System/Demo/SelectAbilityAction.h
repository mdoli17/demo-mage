// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ability System/AbilityAction.h"
#include "DemoAbilityAction.h"
#include "SelectAbilityAction.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_MAGE_API USelectAbilityAction : public UDemoAbilityAction
{
	GENERATED_BODY()

protected:
	virtual bool ExecuteActionImplementation_Implementation(const FActionParams& Params) override;
};
