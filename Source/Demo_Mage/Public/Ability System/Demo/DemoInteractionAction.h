// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DemoAbilityAction.h"
#include "Kismet/KismetSystemLibrary.h"
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
	float InteractionDistance;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Interaction")
	TEnumAsByte<ETraceTypeQuery> TraceChannel;

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
	TArray<AActor*> ActorsToIgnore;
};
