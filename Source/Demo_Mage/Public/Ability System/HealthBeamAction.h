// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BeamAction.h"
#include "HealthBeamAction.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_MAGE_API UHealthBeamAction : public UBeamAction
{
	GENERATED_BODY()

protected:
	virtual void StartHandlingBeamForActor(AActor* Actor) override;
	virtual void StopHandlingBeamForActor(AActor* Actor) override;
	virtual void UpdateHandlingBeamForActor(AActor* Actor) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Health Beam")
	float DamageOverTime;
};
