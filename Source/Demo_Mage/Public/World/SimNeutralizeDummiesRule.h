// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AdvancementRule.h"
#include "SimNeutralizeDummiesRule.generated.h"

class AEnemySpawnPoint;

UCLASS()
class DEMO_MAGE_API ASimNeutralizeDummiesRule : public AAdvancementRule
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASimNeutralizeDummiesRule();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Rules")
	TArray<AEnemySpawnPoint*> SpawnPoints;

	UFUNCTION()
	void EnemyNeutralizeHandler();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
