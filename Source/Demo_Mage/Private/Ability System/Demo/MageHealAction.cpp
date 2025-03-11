// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability System/Demo/MageHealAction.h"

void UMageHealAction::Initialize_Implementation()
{
	Super::Initialize_Implementation();
	AnimInterface->GetAnimNotifyEventReceived().AddDynamic(this, &UMageHealAction::AnimNotifyEventReceivedHandler);
	ActorsToIgnoreDuringTrace.Add(Owner);
}

bool UMageHealAction::StartActionImplementation_Implementation(const FActionParams& Params)
{
	AnimInterface->StartAbility();
	return Super::StartActionImplementation_Implementation(Params);
}

bool UMageHealAction::StopActionImplementation_Implementation()
{
	if (!SetupTarget())
	{
		AnimInterface->StopAbility(false);
		return true;
	}

	AnimInterface->StopAbility();
	return Super::StopActionImplementation_Implementation();
}

void UMageHealAction::Heal()
{
	if (!HealthComponentProvider) return;

	UAttributeComponent* HealthComponent = HealthComponentProvider->GetHealthComponent();
	if (!HealthComponent) return;

	HealthComponent->SingleUse(HealAmount);
}

void UMageHealAction::AnimNotifyEventReceivedHandler(const FAnimNotifyEvent& AnimNotifyEvent)
{
	if (AnimNotifyEvent.NotifyName != AnimNotifyName) return;
	Heal();
	ResetTarget();
}

bool UMageHealAction::SetupTarget()
{
	FVector EyeViewPointLocation;
	FRotator EyeViewPointRotation;
	DemoCharacter->GetActorEyesViewPoint(EyeViewPointLocation, EyeViewPointRotation);

	const FVector TraceStart = EyeViewPointLocation;
	const FVector TraceEnd = TraceStart + EyeViewPointRotation.Vector() * MaxVisionDistance;

	FHitResult Hit;
	UKismetSystemLibrary::SphereTraceSingleForObjects(GetWorld(), TraceStart, TraceEnd, SphereTraceRadius, TraceObjectTypes, false, ActorsToIgnoreDuringTrace, TraceDrawDebugType, Hit, true,
	                                                  TraceColor, TraceHitColor, TraceDrawTime);

	if (!Hit.bBlockingHit) return false;

	AActor* HitActor = Hit.GetActor();
	if (!HitActor->Implements<UHealthComponentProvider>()) return false;

	HealthComponentProvider = Cast<IHealthComponentProvider>(HitActor);

	return true;
}
