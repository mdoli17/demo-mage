// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActionParams.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "AbilityComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DEMO_MAGE_API UAbilityComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	// Sets default values for this component's properties
	UAbilityComponent();

	UFUNCTION(BlueprintCallable, Category="Abilities")
	bool StartActionByName(FName ActionName, const FActionParams& Params = FActionParams());

	UFUNCTION(BlueprintCallable, Category="Abilities")
	bool StopActionByName(FName ActionName);

	UFUNCTION(BlueprintCallable, Category="Abilities")
	bool ExecuteActionByName(FName ActionName, const FActionParams& Params = FActionParams());

	UFUNCTION(BlueprintCallable, Category="Abilities")
	bool IsActionRunning(const FName ActionName);

	UFUNCTION(BlueprintCallable, Category="Abilities")
	void AddAction(TSubclassOf<UAbilityAction> ActionClass);

	UFUNCTION(BlueprintCallable, Category="Abilities")
	void RemoveAction(TSubclassOf<UAbilityAction> ActionClass);

	UFUNCTION(BlueprintCallable, Category="Utilities")
	FName GetNameForAbilityClass(TSubclassOf<UAbilityAction> ActionClass);

	UPROPERTY(BlueprintReadOnly, Category="Abilities")
	FGameplayTagContainer ActiveGameplayTags;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Abilities")
	TArray<TSubclassOf<UAbilityAction>> InitialActions;

	UPROPERTY(BlueprintReadOnly, Category="Abilities")
	TMap<FName, UAbilityAction*> Actions;

	UPROPERTY(BlueprintReadOnly, Category="Abilities")
	TMap<TSubclassOf<UAbilityAction>, UAbilityAction*> ActionsByClass;

private:
	void SetupInitialActions();
};
