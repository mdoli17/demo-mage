// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ability System/AbilityAction.h"
#include "Characters/Animations/DemoCharacterToAnimInterface.h"
#include "DemoAbilityAction.generated.h"

UCLASS()
class DEMO_MAGE_API UDemoAbilityAction : public UAbilityAction
{
	GENERATED_BODY()

protected:
	virtual void Initialize(AActor* Instigator) override;
	virtual void Initialize_Implementation() override;

	virtual UDemoAbilityComponent* GetOwningComponent() const override;

	IDemoCharacterToAnimInterface* AnimInterface;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Action", meta=(AllowPrivateAccess))
	ADemoCharacter* DemoCharacter;
};
