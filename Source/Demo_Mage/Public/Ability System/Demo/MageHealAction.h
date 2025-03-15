// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DemoAbilityAction.h"
#include "Kismet/KismetSystemLibrary.h"
#include "MageHealAction.generated.h"

/**
 * Ability which adds health to any target which inherits IHealthComponentProvider.
 * (In the future, maybe improve this ability, by damaging enemies, and healing allies)
 */
UCLASS()
class DEMO_MAGE_API UMageHealAction : public UDemoAbilityAction
{
	GENERATED_BODY()

public:
	virtual void Initialize_Implementation() override;
	virtual bool StartActionImplementation_Implementation(const FActionParams& Params) override;
	virtual bool StopActionImplementation_Implementation() override;

	void Heal();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Mage Heal")
	float HealAmount;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Mage Heal")
	float MaxVisionDistance;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Mage Heal")
	float SphereTraceRadius;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Mage Heal")
	TArray<TEnumAsByte<EObjectTypeQuery>> TraceObjectTypes;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Mage Heal")
	FName AnimNotifyName;

	UFUNCTION(BlueprintImplementableEvent, Category="Mage Heal")
	void OnCastStarted();

	UFUNCTION(BlueprintImplementableEvent, Category="Mage Heal")
	void OnCastSucceeded();

	UFUNCTION(BlueprintImplementableEvent, Category="Mage Heal")
	void OnCastFailed();

private:
	IHealthComponentProvider* HealthComponentProvider;
	TArray<AActor*> ActorsToIgnoreDuringTrace;

	// TODO: Boiler-plate code, can be refactored by deriving from DemoCharacterAbilityAction which will handle basic repetitive things
	UFUNCTION()
	void AnimNotifyEventReceivedHandler(const FAnimNotifyEvent& AnimNotifyEvent);

	bool SetupTarget();

	void ResetTarget()
	{
		HealthComponentProvider = nullptr;
	}

protected:
	// ----------------- DEBUG ---------------- //
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Mage Heal/Debug")
	TEnumAsByte<EDrawDebugTrace::Type> TraceDrawDebugType = EDrawDebugTrace::Type::None;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Mage Heal/Debug")
	FLinearColor TraceColor = FLinearColor::White;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Mage Heal/Debug")
	FLinearColor TraceHitColor = FLinearColor::Green;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Mage Heal/Debug")
	float TraceDrawTime = 1.5f;
};
