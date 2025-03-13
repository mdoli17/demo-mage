// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DemoAbilityAction.h"
#include "Kismet/KismetSystemLibrary.h"
#include "MageBeamAction.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_MAGE_API UMageBeamAction : public UDemoAbilityAction, public FTickableGameObject
{
	GENERATED_BODY()

public:
	virtual void Initialize_Implementation() override;
	virtual bool StartActionImplementation_Implementation(const FActionParams& Params) override;
	virtual bool StopActionImplementation_Implementation() override;

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
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Mage Beam")
	float DamageOverTime;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Mage Beam")
	float MaxVisionDistance;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Mage Beam")
	float SphereTraceRadius;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Mage Beam")
	TArray<TEnumAsByte<EObjectTypeQuery>> TraceObjectTypes;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Mage Beam")
	FName ReadyToCastAnimNotifyName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Mage Beam")
	FName FinishedCastingAnimNotifyName;

private:
	TArray<AActor*> ActorsToIngoreDuringTrace;

	UPROPERTY()
	AActor* TracedActor;

	IHealthComponentProvider* HealthComponentProvider;

	uint32 LastFrameNumberTicked = -1;
	bool bIsReadyToCast = false;

	UFUNCTION()
	void AnimNotifyEventReceiveHandler(const FAnimNotifyEvent& AnimNotifyEvent);

	void StartDealingDamage();
	void StopDealingDamage();
	void SwitchDealingDamage(IHealthComponentProvider* OldHealthComponentProvider);

protected:
	// ----------------- DEBUG ---------------- //
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Mage Beam/Debug")
	TEnumAsByte<EDrawDebugTrace::Type> TraceDrawDebugType = EDrawDebugTrace::Type::None;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Mage Beam/Debug")
	FLinearColor TraceColor = FLinearColor::White;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Mage Beam/Debug")
	FLinearColor TraceHitColor = FLinearColor::Green;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Mage Beam/Debug")
	float TraceDrawTime = 1.5f;
};
