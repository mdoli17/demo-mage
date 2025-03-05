// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DemoCharacterAnimInterface.h"
#include "DemoCharacterToAnimInterface.h"
#include "Animation/AnimInstance.h"
#include "DemoCharacterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_MAGE_API UDemoCharacterAnimInstance : public UAnimInstance, public IDemoCharacterToAnimInterface
{
	GENERATED_BODY()

public:
	virtual void StartBasicAttack() override
	{
		bIsAttacking = true;
	}

	virtual void StopBasicAttack() override
	{
		bIsAttacking = false;
	}

	virtual FOnBasicAttackReady& GetBasicAttackReadyEvent() override
	{
		return OnBasicAttackReady;
	}

	virtual void SetAbilityType(const EMageAbilityType AbilityType) override
	{
		CurrentAbility = AbilityType;
	}

	virtual void StartAbility() override
	{
		bIsUsingAbility = true;
	}

	virtual void StopAbility() override
	{
		bIsUsingAbility = false;
	}

protected:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	virtual bool HandleNotify(const FAnimNotifyEvent& AnimNotifyEvent) override;

	IDemoCharacterAnimInterface* CharacterInterface = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Locomotion")
	bool bIsMoving;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Locomotion")
	bool bIsSprinting;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Locomotion")
	bool bIsInAir;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Combat")
	bool bIsAttacking;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Combat")
	bool bIsUsingAbility;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Combat")
	EMageAbilityType CurrentAbility;

	UPROPERTY()
	FOnBasicAttackReady OnBasicAttackReady;
};
