// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilityAction.h"
#include "DemoCharacterToAnimInterface.h"
#include "DemoAbilityAction.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_MAGE_API UDemoAbilityAction : public UAbilityAction
{
	GENERATED_BODY()

protected:
	virtual void Initialize_Implementation() override;

	UFUNCTION(BlueprintCallable, Category="Demo Ability Ability Action")
	virtual UDemoAbilityComponent* GetOwningComponent() const override;

	UFUNCTION(BlueprintCallable, Category="Demo Ability Ability Action")
	IDemoCharacterToAnimInterface* AnimInterface;
};
