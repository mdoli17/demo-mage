// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ECharacterAbilityType.h"
#include "DemoCharacterToAnimInterface.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBasicAttackReady);


// This class does not need to be modified.
UINTERFACE(NotBlueprintable)
class UDemoCharacterToAnimInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DEMO_MAGE_API IDemoCharacterToAnimInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	virtual void StartBasicAttack() = 0;

	UFUNCTION(BlueprintCallable)
	virtual void StopBasicAttack() = 0;

	virtual FOnBasicAttackReady& GetBasicAttackReadyEvent() = 0;

	virtual void SetAbilityType(const ECharacterAbilityType AbilityType) = 0;

	UFUNCTION(BlueprintCallable)
	virtual void StartAbility() = 0;

	UFUNCTION(BlueprintCallable)
	virtual void StopAbility() = 0;
};
