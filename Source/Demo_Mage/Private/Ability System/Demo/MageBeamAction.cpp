// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability System/Demo/MageBeamAction.h"

void UMageBeamAction::Initialize_Implementation()
{
	Super::Initialize_Implementation();

	AnimInterface = Cast<IDemoCharacterToAnimInterface>(DemoCharacter->GetSkeletalMesh()->GetAnimInstance());
	ensure(AnimInterface);
	Super::Initialize_Implementation();

	AnimInterface->GetAnimNotifyEventReceived().AddDynamic(this, &UMageBeamAction::AnimNotifyEventReceiveHandler);
}


bool UMageBeamAction::StartActionImplementation_Implementation(const FActionParams& Params)
{
	AnimInterface->StartAbility();
	return true;
}

bool UMageBeamAction::StopActionImplementation_Implementation()
{
	AnimInterface->StopAbility(true);
	return true;
}

void UMageBeamAction::StartHandlingBeamForActor(AActor* Actor)
{
	Super::StartHandlingBeamForActor(Actor);

	if (Actor == nullptr) return;
	IHealthComponentProvider* HealthComponentProvider = Cast<IHealthComponentProvider>(Actor);

	if (!HealthComponentProvider) return;

	UAttributeComponent* HealthComponent = HealthComponentProvider->GetHealthComponent();
	HealthComponent->StartUsing(DamageOverTime);
}

void UMageBeamAction::StopHandlingBeamForActor(AActor* Actor)
{
	Super::StopHandlingBeamForActor(Actor);

	if (Actor == nullptr) return;
	IHealthComponentProvider* HealthComponentProvider = Cast<IHealthComponentProvider>(Actor);

	if (!HealthComponentProvider) return;

	UAttributeComponent* HealthComponent = HealthComponentProvider->GetHealthComponent();
	HealthComponent->StopUsing(DamageOverTime);
}

void UMageBeamAction::UpdateHandlingBeamForActor(AActor* Actor)
{
	Super::UpdateHandlingBeamForActor(Actor);
}

void UMageBeamAction::AnimNotifyEventReceiveHandler(const FAnimNotifyEvent& AnimNotifyEvent)
{
	if (AnimNotifyEvent.NotifyName == ReadyToCastAnimNotifyName)
	{
		bCanBeam = true;
		// Calling on next tick to ensure references are updated
		GetWorld()->GetTimerManager().SetTimerForNextTick(this, &UMageBeamAction::OnCastStarted);
	}
	if (AnimNotifyEvent.NotifyName == FinishedCastingAnimNotifyName)
	{
		Super::StopActionImplementation_Implementation();
		GetWorld()->GetTimerManager().SetTimerForNextTick(this, &UMageBeamAction::OnCastEnded);
	}
}
