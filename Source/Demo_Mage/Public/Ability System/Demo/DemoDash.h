// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DemoAbilityAction.h"
#include "DemoDash.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_MAGE_API UDemoDash : public UDemoAbilityAction, public FTickableGameObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
	void Tick(float DeltaTime) override;

	virtual ETickableTickType GetTickableTickType() const override
	{
		return ETickableTickType::Always;
	}

	virtual TStatId GetStatId() const override
	{
		RETURN_QUICK_DECLARE_CYCLE_STAT(FBeamAction, STATGROUP_Tickables);
	}

	virtual bool IsTickableWhenPaused() const override
	{
		return false;
	}

	virtual bool IsTickableInEditor() const override
	{
		return false;
	}
};
