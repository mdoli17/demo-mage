// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Camera")
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Demo Character")
	TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;

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

	UFUNCTION()
	void MoveInputCallback(const FInputActionValue& Value);

	UFUNCTION()
	void SprintInputCallback(const FInputActionValue& Value);

	UFUNCTION()
	void JumpInputCallback(const FInputActionValue& Value);

	UFUNCTION()
	void CameraMovementInputCallback(const FInputActionValue& Value);


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
};
