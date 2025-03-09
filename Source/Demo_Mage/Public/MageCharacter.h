// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DemoCharacter.h"
#include "InputActionValue.h"
#include "Camera/CameraComponent.h"
#include "MageCharacter.generated.h"

class UInputAction;
class UInputMappingContext;

UCLASS()
class DEMO_MAGE_API AMageCharacter : public ADemoCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMageCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual USkeletalMeshComponent* GetSkeletalMesh() const override
	{
		return SkeletalMeshComponent;
	}

	const UCameraComponent* GetCamera() const
	{
		return CameraComponent;
	}

protected:
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Input")
	TSoftObjectPtr<UInputAction> SelectAbilityAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Input")
	TSoftObjectPtr<UInputAction> AbilityAction;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Demo Character")
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Demo Character")
	TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;

	
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

	UFUNCTION()
	void SelectAbilityInputCallback(const FInputActionValue& Value);

	UFUNCTION()
	void AbilityActionInputCallback(const FInputActionValue& Value);
};
