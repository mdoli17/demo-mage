// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/EnemyCharacter.h"

#include "GameFramework/PawnMovementComponent.h"


// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetMesh()->SetCollisionProfileName("Ragdoll");
}


void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	HealthComponent->OnAttributeDepleted.AddDynamic(this, &AEnemyCharacter::HealthDepleteHandler);
}

void AEnemyCharacter::HealthDepleteHandler()
{
	UPawnMovementComponent* PawnMovementComponent = GetMovementComponent();
	PawnMovementComponent->Deactivate();
	HealthComponent->Deactivate();

	OnDeath();
}
