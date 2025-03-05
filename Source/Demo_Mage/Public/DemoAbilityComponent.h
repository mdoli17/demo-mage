// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilityComponent.h"
#include "ECharacterAbilityType.h"
#include "DemoAbilityComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DEMO_MAGE_API UDemoAbilityComponent : public UAbilityComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UDemoAbilityComponent();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Demo Abilities")
	ECharacterAbilityType SelectedAbility;

public:
	UFUNCTION(BlueprintCallable, Category="Demo Abilities")
	void SelectAbility(const ECharacterAbilityType AbilityType)
	{
		SelectedAbility = AbilityType;
	}

	UFUNCTION(BlueprintCallable, Category="Demo Abilities")
	ECharacterAbilityType GetSelectedAbility() const
	{
		return SelectedAbility;
	}
};
