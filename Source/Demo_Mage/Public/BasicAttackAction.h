// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilityAction.h"
#include "DemoCharacterToAnimInterface.h"
#include "DemoProjectile.h"
#include "BasicAttackAction.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_MAGE_API UBasicAttackAction : public UAbilityAction
{
	GENERATED_BODY()

public:
	virtual void Initialize_Implementation() override;
	virtual bool StartActionImplementation_Implementation(const FActionParams& Params) override;
	virtual bool StopActionImplementation_Implementation() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Basic Attack")
	TSubclassOf<ADemoProjectile> ProjectileClass;
	
private:
	IDemoCharacterToAnimInterface* AnimInterface;

	UFUNCTION()
	void BasicAttackActionReadyCallback();
};
