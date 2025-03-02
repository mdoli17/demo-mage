// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DemoCharacterAnimInterface.h"
#include "Animation/AnimInstance.h"
#include "DemoCharacterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_MAGE_API UDemoCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	IDemoCharacterAnimInterface* CharacterInterface = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Locomotion")
	bool bIsMoving;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Locomotion")
	bool bIsSprinting;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Locomotion")
	bool bIsInAir;
};
