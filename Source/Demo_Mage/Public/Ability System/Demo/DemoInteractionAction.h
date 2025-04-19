// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DemoAbilityAction.h"
#include "Tools/Tracing/TraceData.h"
#include "DemoInteractionAction.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_MAGE_API UDemoInteractionAction : public UDemoAbilityAction
{
	GENERATED_BODY()

public:
	virtual bool ExecuteActionImplementation_Implementation(const FActionParams& Params) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Interaction")
	FTraceData TraceData;

private:
	TArray<AActor*> ActorsToIgnore;
};
