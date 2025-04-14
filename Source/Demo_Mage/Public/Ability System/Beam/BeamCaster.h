// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BeamCaster.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UBeamCaster : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DEMO_MAGE_API IBeamCaster
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, Category="Beam")
	FVector GetBeamStart();

	UFUNCTION(BlueprintNativeEvent, Category="Beam")
	FVector GetBeamEnd();
};
