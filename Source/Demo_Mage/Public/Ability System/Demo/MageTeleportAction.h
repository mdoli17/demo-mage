// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DemoAbilityAction.h"
#include "Kismet/KismetSystemLibrary.h"
#include "MageTeleportAction.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_MAGE_API UMageTeleportAction : public UDemoAbilityAction
{
	GENERATED_BODY()

public:
	virtual void Initialize_Implementation() override;
	virtual bool StartActionImplementation_Implementation(const FActionParams& Params) override;
	virtual bool StopActionImplementation_Implementation() override;

	void TeleportTargets() const;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Mage Teleport")
	float MaxVisionDistance = 1000.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Mage Teleport")
	float SphereTraceRadius = 250.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Mage Teleport")
	TArray<TEnumAsByte<EObjectTypeQuery>> TraceObjectTypes;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Mage Teleport")
	FName AnimNotifyName;

private:
	TArray<AActor*> ActorsToIgnoreDuringTrace;
	AActor* InitialTarget;
	AActor* FinalTarget;

	UFUNCTION()
	void AbilityReadyCallback();

	UFUNCTION()
	void AnimNotifyEventReceivedHandler(const FAnimNotifyEvent& AnimNotifyEvent);

	bool SetupInitialTarget();
	bool SetupFinalTarget();

	void SphereTrace(FHitResult& Hit) const;

	void ResetTargets()
	{
		InitialTarget = nullptr;
		FinalTarget = nullptr;
	}

protected:
	// ----------------- DEBUG ---------------- //
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Mage Teleport/Debug")
	TEnumAsByte<EDrawDebugTrace::Type> TraceDrawDebugType = EDrawDebugTrace::Type::None;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Mage Teleport/Debug")
	FLinearColor TraceColor = FLinearColor::White;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Mage Teleport/Debug")
	FLinearColor TraceHitColor = FLinearColor::Green;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Mage Teleport/Debug")
	float TraceDrawTime = 1.5f;
};
