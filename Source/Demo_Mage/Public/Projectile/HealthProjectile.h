// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DemoProjectile.h"
#include "Attribute System/HealthComponentProvider.h"
#include "HealthProjectile.generated.h"

UCLASS()
class DEMO_MAGE_API AHealthProjectile : public ADemoProjectile
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AHealthProjectile();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Health Projectile")
	float HealthModifyAmount = 0.0f;

	virtual void OnProjectileBeginOverlap_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                                                     const FHitResult& SweepResult) override;
};
