// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DemoCharacterToAnimInterface.generated.h"

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

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable)
	virtual void StartBasicAttack() = 0;

	UFUNCTION(BlueprintCallable)
	virtual void StopBasicAttack() = 0;
};
