// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawn Points/EnemySpawnPoint.h"

#include "Characters/EnemyCharacter.h"


// Sets default values
AEnemySpawnPoint::AEnemySpawnPoint()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AEnemySpawnPoint::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemySpawnPoint::RespawnCharacter()
{
	if (CharacterInstance)
	{
		// Handle ReInitialization
		CharacterInstance->RespawnCharacter();
	}
	else
	{
		FActorSpawnParameters Params;
		Params.Owner = this;
		CharacterInstance = GetWorld()->SpawnActor<AEnemyCharacter>(EnemyCharacterClass, GetActorLocation() + SpawnLocation, GetActorForwardVector().Rotation(), Params);
		CharacterInstance->SpawnDefaultController();

		CharacterInstance->OnDeathDelegate.AddDynamic(this, &AEnemySpawnPoint::CharacterDeathHandler);
	}
}

void AEnemySpawnPoint::CharacterDeathHandler()
{
	GetWorld()->GetTimerManager().SetTimer(DeathTimerHandle, this, &AEnemySpawnPoint::RespawnCharacter, RespawnDelay, false);
}
