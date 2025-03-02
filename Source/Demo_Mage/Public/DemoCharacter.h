// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DemoCharacterAnimInterface.h"
#include "GameFramework/Character.h"
#include "DemoCharacter.generated.h"

UCLASS()
class DEMO_MAGE_API ADemoCharacter : public ACharacter, public IDemoCharacterAnimInterface
{
private:
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADemoCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Animation Interface
	virtual bool GetIsMoving() override;
	virtual bool GetIsSprinting() override;
	virtual bool GetIsInAir() override;
	virtual bool GetIsBasicAttacking() override;
};
