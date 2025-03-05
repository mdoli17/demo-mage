// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilityAction.h"
#include "SelectAbilityAction.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_MAGE_API USelectAbilityAction : public UAbilityAction
{
	GENERATED_BODY()

public:
	virtual bool ExecuteActionImplementation_Implementation(const FActionParams& Params) override;
};
