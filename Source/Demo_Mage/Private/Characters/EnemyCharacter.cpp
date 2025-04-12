// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/EnemyCharacter.h"

#include "GameFramework/PawnMovementComponent.h"
#include "Components/CapsuleComponent.h"


// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}


void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	MeshAttachmentLocation = GetMesh()->GetRelativeLocation();
	MeshAttachmentRotation = GetMesh()->GetRelativeRotation();
}

void AEnemyCharacter::RespawnCharacter()
{
	OnRespawn();

	GetMesh()->SetCollisionProfileName("CharacterMesh");

	USkeletalMeshComponent* SkeletalMesh = GetMesh();
	SkeletalMesh->SetSimulatePhysics(false);
	SkeletalMesh->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	SkeletalMesh->AttachToComponent(GetCapsuleComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	SkeletalMesh->SetRelativeLocation(MeshAttachmentLocation);
	SkeletalMesh->SetRelativeRotation(MeshAttachmentRotation);

	if (UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance())
	{
		AnimInstance->InitializeAnimation();
	}

	if (!AIController)
	{
		SpawnDefaultController();
	}
	else
	{
		AIController->Possess(this);
	}

	HealthComponent->Reset();
	HealthComponent->Activate();

	UPawnMovementComponent* PawnMovementComponent = GetMovementComponent();
	PawnMovementComponent->Activate(true);

	Super::RespawnCharacter();
}

void AEnemyCharacter::HealthDepleteHandler()
{
	GetMesh()->SetCollisionProfileName("Ragdoll");

	AIController = GetController();

	if (AIController)
	{
		AIController->UnPossess();
	}

	UPawnMovementComponent* PawnMovementComponent = GetMovementComponent();
	PawnMovementComponent->StopMovementImmediately();
	PawnMovementComponent->Deactivate();
	HealthComponent->Deactivate();

	OnDeath();

	Super::HealthDepleteHandler();
}
