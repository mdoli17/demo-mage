#pragma once

#include "CoreMinimal.h"
#include "DemoCharacter.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class DEMO_MAGE_API AEnemyCharacter : public ADemoCharacter
{
	GENERATED_BODY()

public:
	AEnemyCharacter();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void HealthDepleteHandler();

	UFUNCTION(BlueprintImplementableEvent, Category="Enemy Character")
	void OnDeath();
};
