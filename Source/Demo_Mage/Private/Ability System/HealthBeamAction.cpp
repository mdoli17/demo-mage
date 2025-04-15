// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability System/HealthBeamAction.h"

void UHealthBeamAction::StartHandlingBeamForActor(AActor* Actor)
{
	Super::StartHandlingBeamForActor(Actor);

	if (Actor == nullptr) return;
	IHealthComponentProvider* HealthComponentProvider = Cast<IHealthComponentProvider>(Actor);

	if (!HealthComponentProvider) return;

	UAttributeComponent* HealthComponent = HealthComponentProvider->GetHealthComponent();
	HealthComponent->StartUsing(DamageOverTime);
}

void UHealthBeamAction::StopHandlingBeamForActor(AActor* Actor)
{
	Super::StopHandlingBeamForActor(Actor);

	if (Actor == nullptr) return;
	IHealthComponentProvider* HealthComponentProvider = Cast<IHealthComponentProvider>(Actor);

	if (!HealthComponentProvider) return;

	UAttributeComponent* HealthComponent = HealthComponentProvider->GetHealthComponent();
	HealthComponent->StopUsing(DamageOverTime);
}

void UHealthBeamAction::UpdateHandlingBeamForActor(AActor* Actor)
{
	Super::UpdateHandlingBeamForActor(Actor);
}
