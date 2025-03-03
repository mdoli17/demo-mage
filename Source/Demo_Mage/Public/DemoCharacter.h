// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilityComponent.h"
#include "DemoCharacterAnimInterface.h"
#include "InputActionValue.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "DemoCharacter.generated.h"

class UInputAction;
class UInputMappingContext;

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

protected:
	UFUNCTION()
	void MoveInputCallback(const FInputActionValue& Value);

	UFUNCTION()
	void SprintInputCallback(const FInputActionValue& Value);

	UFUNCTION()
	void JumpInputCallback(const FInputActionValue& Value);

	UFUNCTION()
	void CameraMovementInputCallback(const FInputActionValue& Value);

	UFUNCTION()
	void BasicAttackInputCallback(const FInputActionValue& Value);

	// ------------------- Demo Character ------------------- //
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Demo Character")
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Demo Character")
	TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Demo Character")
	TObjectPtr<UAbilityComponent> AbilityComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Demo Character")
	float WalkSpeed = 250.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Demo Character")
	float SprintSpeed = 600.f;


	// ------------------- Enhanced Input ------------------- //
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Input")
	TSoftObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Input")
	TSoftObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Input")
	TSoftObjectPtr<UInputAction> SprintAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Input")
	TSoftObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Input")
	TSoftObjectPtr<UInputAction> CameraMovementAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Input")
	TSoftObjectPtr<UInputAction> BasicAttackAction;
};
