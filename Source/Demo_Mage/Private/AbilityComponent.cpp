// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityComponent.h"
#include "AbilityAction.h"


// Sets default values for this component's properties
UAbilityComponent::UAbilityComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UAbilityComponent::BeginPlay()
{
	Super::BeginPlay();

	SetupInitialActions();
}

bool UAbilityComponent::StartActionByName(FName ActionName, const FActionParams& Params)
{
	if (!Actions.Contains(ActionName)) return false;

	UAbilityAction* ActionToStart = Actions[ActionName];

	if (!ActionToStart->CanStartAction()) return false;

	return ActionToStart->StartAction(Params);
}

bool UAbilityComponent::StopActionByName(FName ActionName)
{
	if (!Actions.Contains(ActionName)) return false;

	UAbilityAction* ActionToStop = Actions[ActionName];

	if (!ActionToStop->IsRunning()) return false;

	return ActionToStop->StopAction();
}

bool UAbilityComponent::IsActionRunning(const FName ActionName)
{
	if (!Actions.Contains(ActionName)) return false;

	const UAbilityAction* Action = Actions[ActionName];

	return Action->IsRunning();
}


void UAbilityComponent::AddAction(TSubclassOf<UAbilityAction> ActionClass)
{
	if (!ensure(ActionClass)) return;

	UAbilityAction* NewAction = NewObject<UAbilityAction>(this, ActionClass);
	if (NewAction == nullptr) return;

	AActor* Owner = GetOwner();

	NewAction->Initialize(Owner);
	Actions.Add(NewAction->GetActionName(), NewAction);
}

void UAbilityComponent::RemoveAction(TSubclassOf<UAbilityAction> ActionClass)
{
	if (!ensure(ActionClass)) return;

	// TODO: Implement removing action.
}

void UAbilityComponent::SetupInitialActions()
{
	for (const TSubclassOf<UAbilityAction> InitialAction : InitialActions)
	{
		AddAction(InitialAction);
	}
}
