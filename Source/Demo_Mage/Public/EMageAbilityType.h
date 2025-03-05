#pragma once

#include "EMageAbilityType.generated.h"

UENUM(BlueprintType)
enum class EMageAbilityType : uint8
{
	Heal = 0 UMETA(DisplayName = "Heal"),
	Teleport = 1 UMETA(DisplayName = "Teleport"),
	Beam = 2 UMETA(DisplayName = "Beam")
};
