// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ability System/AbilityAction.h"
#include "DemoAbilityAction.h"
#include "Projectile/DemoProjectile.h"
#include "SpawnProjectileAction.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_MAGE_API USpawnProjectileAction : public UDemoAbilityAction
{
	GENERATED_BODY()

public:
	virtual void Initialize_Implementation() override;
	virtual bool StartActionImplementation_Implementation(const FActionParams& Params) override;
	virtual bool StopActionImplementation_Implementation() override;

	void LaunchProjectile() const;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Basic Attack")
	TSubclassOf<ADemoProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Basic Attack")
	FName AnimNotifyName;

private:
	UFUNCTION()
	void AnimNotifyEventReceivedHandler(const FAnimNotifyEvent& AnimNotifyEvent);
};
