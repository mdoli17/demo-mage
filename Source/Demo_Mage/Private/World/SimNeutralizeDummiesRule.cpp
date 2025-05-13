// Fill out your copyright notice in the Description page of Project Settings.


#include "World/SimNeutralizeDummiesRule.h"
#include "Spawn Points/EnemySpawnPoint.h"

// Sets default values
ASimNeutralizeDummiesRule::ASimNeutralizeDummiesRule()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASimNeutralizeDummiesRule::BeginPlay()
{
	Super::BeginPlay();

	for (auto SpawnPoint : SpawnPoints)
	{
		SpawnPoint->OnCharacterNeutralized.AddUniqueDynamic(this, &ASimNeutralizeDummiesRule::EnemyNeutralizeHandler);
	}
}

// Called every frame
void ASimNeutralizeDummiesRule::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASimNeutralizeDummiesRule::EnemyNeutralizeHandler()
{
	for (auto SpawnPoint : SpawnPoints)
	{
		if (SpawnPoint->IsCharacterAlive()) return;
	}

	SatisfyRule();
}
