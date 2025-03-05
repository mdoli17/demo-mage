#pragma once

#include "ECharacterAbilityType.generated.h"

UENUM(BlueprintType)
enum class ECharacterAbilityType : uint8
{
	None = 0 UMETA(DIsplayName = "None"),
	Main = 1 UMETA(DisplayName = "Main"),
	Secondary = 2 UMETA(DisplayName = "Secondary"),
	Support = 3 UMETA(DisplayName = "Support")
};
