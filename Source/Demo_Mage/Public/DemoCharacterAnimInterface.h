// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DemoCharacterAnimInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UDemoCharacterAnimInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DEMO_MAGE_API IDemoCharacterAnimInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual bool GetIsMoving() = 0;
	virtual bool GetIsSprinting() = 0;
	virtual bool GetIsJumping() = 0;

	virtual bool GetIsBasicAttacking() = 0;

	// virtual void SetSpell() = 0;
	// virtual void StartAbility() = 0;
	// virtual void StopAbility() = 0;
};
