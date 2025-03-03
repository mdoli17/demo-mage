// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityAction.h"
#include "AbilityComponent.h"

void UAbilityAction::Initialize(AActor* Instigator)
{
	Owner = Instigator;
	Initialize();
}


bool UAbilityAction::StartAction(const FActionParams& Params)
{
	UE_LOG(LogTemp, Log, TEXT("Trying to start Action: %s"), *Name.ToString());

	bIsRunning = StartActionImplementation(Params);

	if (bIsRunning)
	{
		UAbilityComponent* ActionComponent = GetOwningComponent();
		ActionComponent->ActiveGameplayTags.AppendTags(GrantingTags);
	}

	return bIsRunning;
}

bool UAbilityAction::StopAction()
{
	UE_LOG(LogTemp, Log, TEXT("Stoping Action: %s"), *Name.ToString());

	ensureAlways(bIsRunning);

	const bool bActionStopped = StopActionImplementation();

	if (bActionStopped)
	{
		bIsRunning = false;
		UAbilityComponent* ActionComponent = GetOwningComponent();
		ActionComponent->ActiveGameplayTags.RemoveTags(GrantingTags);
	}

	return bActionStopped;;
}

bool UAbilityAction::CanStartAction_Implementation()
{
	const UAbilityComponent* ActionComponent = GetOwningComponent();

	return !ActionComponent->ActiveGameplayTags.HasAny(BlockingTags);
}

UAbilityComponent* UAbilityAction::GetOwningComponent() const
{
	return Cast<UAbilityComponent>(GetOuter());
}

void UAbilityAction::Initialize_Implementation()
{
}

bool UAbilityAction::StartActionImplementation_Implementation(const FActionParams& Params)
{
	return true;
}

bool UAbilityAction::StopActionImplementation_Implementation()
{
	return true;
}
