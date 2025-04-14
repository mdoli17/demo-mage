// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DemoAbilityAction.h"
#include "Ability System/BeamAction.h"
#include "MageBeamAction.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_MAGE_API UMageBeamAction : public UBeamAction
{
	GENERATED_BODY()

public:
	virtual void Initialize_Implementation() override;
	virtual bool StartActionImplementation_Implementation(const FActionParams& Params) override;
	virtual bool StopActionImplementation_Implementation() override;

protected:
	virtual UDemoAbilityComponent* GetOwningComponent() const override
	{
		return Cast<UDemoAbilityComponent>(GetOuter());
	}

	virtual void StartHandlingBeamForActor(AActor* Actor) override;
	virtual void StopHandlingBeamForActor(AActor* Actor) override;
	virtual void UpdateHandlingBeamForActor(AActor* Actor) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Mage Beam")
	float DamageOverTime;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Mage Beam")
	float MaxVisionDistance;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Mage Beam")
	FName ReadyToCastAnimNotifyName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Mage Beam")
	FName FinishedCastingAnimNotifyName;

	UFUNCTION(BlueprintImplementableEvent, Category="Mage Beam")
	void OnCastStarted();

	UFUNCTION(BlueprintImplementableEvent, Category="Mage Beam")
	void OnCastEnded();

	IDemoCharacterToAnimInterface* AnimInterface;

private:
	UFUNCTION()
	void AnimNotifyEventReceiveHandler(const FAnimNotifyEvent& AnimNotifyEvent);
};
