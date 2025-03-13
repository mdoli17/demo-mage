// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability System/Demo/MageBeamAction.h"

void UMageBeamAction::Initialize_Implementation()
{
	Super::Initialize_Implementation();

	AnimInterface->GetAnimNotifyEventReceived().AddDynamic(this, &UMageBeamAction::AnimNotifyEventReceiveHandler);
	ActorsToIngoreDuringTrace.Add(Owner);
}


bool UMageBeamAction::StartActionImplementation_Implementation(const FActionParams& Params)
{
	bIsReadyToCast = true;
	AnimInterface->StartAbility();
	return true;
}

bool UMageBeamAction::StopActionImplementation_Implementation()
{
	bIsReadyToCast = false;
	AnimInterface->StopAbility(true);
	return true;
}

void UMageBeamAction::Tick(float DeltaTime)
{
	if (bIsReadyToCast) // Can sphere cast
	{
		FVector EyeViewPointLocation;
		FRotator EyeViewPointRotation;
		DemoCharacter->GetActorEyesViewPoint(EyeViewPointLocation, EyeViewPointRotation);

		const FVector TraceStart = EyeViewPointLocation;
		const FVector TraceEnd = TraceStart + EyeViewPointRotation.Vector() * MaxVisionDistance;

		FHitResult Hit;
		UKismetSystemLibrary::SphereTraceSingleForObjects(GetWorld(), TraceStart, TraceEnd, SphereTraceRadius, TraceObjectTypes, false, ActorsToIngoreDuringTrace, TraceDrawDebugType, Hit, true,
		                                                  TraceColor, TraceHitColor, TraceDrawTime);

		if (Hit.bBlockingHit)
		{
			AActor* HitActor = Hit.GetActor();
			if (HitActor != TracedActor)
			{
				TracedActor = HitActor;
				IHealthComponentProvider* OldHealthComponentProvider = HealthComponentProvider;
				if (HitActor->Implements<UHealthComponentProvider>())
				{
					HealthComponentProvider = Cast<IHealthComponentProvider>(HitActor);
				}
				else
				{
					HealthComponentProvider = nullptr;
				}
				SwitchDealingDamage(OldHealthComponentProvider);
			}
		}
		else
		{
			TracedActor = nullptr;
			HealthComponentProvider = nullptr;
		}
	}
}

void UMageBeamAction::AnimNotifyEventReceiveHandler(const FAnimNotifyEvent& AnimNotifyEvent)
{
	if (AnimNotifyEvent.NotifyName == ReadyToCastAnimNotifyName)
	{
		StartDealingDamage();
	}
	if (AnimNotifyEvent.NotifyName == FinishedCastingAnimNotifyName)
	{
		StopDealingDamage();
	}
}

void UMageBeamAction::StartDealingDamage()
{
	if (!HealthComponentProvider) return;

	UAttributeComponent* HealthComponent = HealthComponentProvider->GetHealthComponent();
	if (!ensure(HealthComponent)) return;

	HealthComponent->StartUsing(DamageOverTime);
}

void UMageBeamAction::StopDealingDamage()
{
	if (!HealthComponentProvider) return;

	UAttributeComponent* HealthComponent = HealthComponentProvider->GetHealthComponent();
	if (!ensure(HealthComponent)) return;

	HealthComponent->StopUsing(DamageOverTime);
}

void UMageBeamAction::SwitchDealingDamage(IHealthComponentProvider* OldHealthComponentProvider)
{
	if (OldHealthComponentProvider != nullptr)
	{
		UAttributeComponent* OldHealthComponent = OldHealthComponentProvider->GetHealthComponent();
		if (!ensure(OldHealthComponent)) return;
		OldHealthComponent->StopUsing(DamageOverTime);
	}

	if (!HealthComponentProvider) return;

	UAttributeComponent* NewHealthComponent = HealthComponentProvider->GetHealthComponent();
	if (!ensure(NewHealthComponent)) return;

	NewHealthComponent->StartUsing(DamageOverTime);
}
