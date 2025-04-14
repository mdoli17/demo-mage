// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilityAction.h"
#include "Beam/BeamCaster.h"
#include "Kismet/KismetSystemLibrary.h"
#include "BeamAction.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_MAGE_API UBeamAction : public UAbilityAction, public FTickableGameObject
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;

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

protected:
	virtual void Initialize_Implementation() override;
	virtual bool StartActionImplementation_Implementation(const FActionParams& Params) override;
	virtual bool StopActionImplementation_Implementation() override;

	UFUNCTION(BlueprintNativeEvent, Category="Beam")
	FVector GetTraceStart();

	UFUNCTION(BlueprintNativeEvent, Category="Beam")
	FVector GetTraceEnd();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Beam")
	float SphereTraceRadius;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Beam")
	TArray<TEnumAsByte<EObjectTypeQuery>> TraceObjectTypes;

	// ----------------- DEBUG ---------------- //
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Debug")
	TEnumAsByte<EDrawDebugTrace::Type> TraceDrawDebugType = EDrawDebugTrace::Type::None;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Debug")
	FLinearColor TraceColor = FLinearColor::White;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Debug")
	FLinearColor TraceHitColor = FLinearColor::Green;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Debug")
	float TraceDrawTime = 1.5f;

private:
	bool bCanBeam;

	TArray<AActor*> ActorsToIngoreDuringTrace;

	AActor* TracedActor;
	AActor* Caster;
};
