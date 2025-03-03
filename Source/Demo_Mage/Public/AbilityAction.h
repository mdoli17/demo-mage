// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActionParams.h"
#include "DemoCharacter.h"
#include "GameplayTagContainer.h"
#include "UObject/Object.h"
#include "AbilityAction.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, Abstract)
class DEMO_MAGE_API UAbilityAction : public UObject
{
	GENERATED_BODY()

public:
	virtual void Initialize(AActor* Instigator);

	UFUNCTION(BlueprintNativeEvent, Category="Action")
	bool CanStartAction();

	UFUNCTION(BlueprintCallable, Category="Action")
	virtual bool StartAction(const FActionParams& Params);

	UFUNCTION(BlueprintCallable, Category="Action")
	bool StopAction();

	UFUNCTION(BlueprintCallable, Category="Action")
	FName GetActionName() const
	{
		return Name;
	}

	UFUNCTION(BlueprintCallable, Category="Action")
	bool IsRunning() const
	{
		return bIsRunning;
	}

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Action")
	FGameplayTagContainer GrantingTags;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Action")
	FGameplayTagContainer BlockingTags;

protected:
	UFUNCTION(BlueprintNativeEvent, Category="Action")
	void Initialize();

	UFUNCTION(BlueprintNativeEvent, Category="Action")
	bool StartActionImplementation(const FActionParams& Params);

	UFUNCTION(BlueprintNativeEvent, Category="Action")
	bool StopActionImplementation();

	UFUNCTION(BlueprintCallable, Category="Action")
	UAbilityComponent* GetOwningComponent() const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Action", meta=(AllowPrivateAccess))
	FName Name;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Action", meta=(AllowPrivateAccess))
	AActor* Owner;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Action", meta=(AllowPrivateAccess))
	ADemoCharacter* DemoCharacter;

	bool bIsRunning;
};
