#pragma once
#include "Kismet/KismetSystemLibrary.h"
#include "TraceData.generated.h"

USTRUCT(BlueprintType)
struct FTraceData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Trace Data")
	float TraceLength = 0.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Trace Data")
	bool bTraceComplex = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Trace Data")
	bool bIgnoreSelf = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Trace Data")
	TEnumAsByte<ETraceTypeQuery> TraceChannel;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Trace Data")
	TEnumAsByte<EDrawDebugTrace::Type> TraceDrawDebugType = EDrawDebugTrace::Type::None;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Trace Data")
	FLinearColor TraceColor = FLinearColor::White;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Trace Data")
	FLinearColor TraceHitColor = FLinearColor::Green;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Trace Data")
	float TraceDrawTime = 1.5f;
};
