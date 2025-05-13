// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawnPoint.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCharacterNeutralized);

class AEnemyCharacter;

UCLASS()
class DEMO_MAGE_API AEnemySpawnPoint : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEnemySpawnPoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Spawn Point")
	TSubclassOf<AEnemyCharacter> EnemyCharacterClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Spawn Point", Meta = (MakeEditWidget = true))
	FVector SpawnLocation;

	UFUNCTION(BlueprintCallable)
	void RespawnCharacter();

	UPROPERTY(BlueprintAssignable)
	FOnCharacterNeutralized OnCharacterNeutralized;

	UFUNCTION(BlueprintCallable, Category="Spawn Point")
	bool IsCharacterAlive() const
	{
		return bIsAlive;
	}

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Spawn Point")
	float RespawnDelay;

	AEnemyCharacter* CharacterInstance;

	UFUNCTION()
	void CharacterDeathHandler();

private:
	FTimerHandle DeathTimerHandle;

	bool bIsAlive;
};
