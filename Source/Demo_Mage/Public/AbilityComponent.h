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

	virtual void BeginPlay() override;

public:
	// Sets default values for this component's properties
	UAbilityComponent();

	UFUNCTION(BlueprintCallable, Category="Actions")
	bool StartActionByName(FName ActionName, const FActionParams& Params = FActionParams());

	UFUNCTION(BlueprintCallable, Category="Actions")
	bool StopActionByName(FName ActionName);

	UFUNCTION(BlueprintCallable, Category="Actions")
	void AddAction(TSubclassOf<UAbilityAction> ActionClass);

	UFUNCTION(BlueprintCallable, Category="Actions")
	void RemoveAction(TSubclassOf<UAbilityAction> ActionClass);

	UPROPERTY(BlueprintReadOnly, Category="Actions")
	FGameplayTagContainer ActiveGameplayTags;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Actions")
	TArray<TSubclassOf<UAbilityAction>> InitialActions;

	UPROPERTY(BlueprintReadOnly, Category="Actions")
	TMap<FName, UAbilityAction*> Actions;

private:
	void SetupInitialActions();
};
