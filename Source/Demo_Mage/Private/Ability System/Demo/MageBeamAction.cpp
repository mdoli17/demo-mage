// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability System/Demo/MageBeamAction.h"

void UMageBeamAction::Initialize_Implementation()
{
	Super::Initialize_Implementation();

	AnimInterface->GetAnimNotifyEventReceived().AddDynamic(this, &UMageBeamAction::AnimNotifyEventRecieveHandler);
	ActorsToIngoreDuringTrace.Add(Owner);
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
	}
}

void UMageBeamAction::AnimNotifyEventRecieveHandler(const FAnimNotifyEvent& AnimNotifyEvent)
{
	if (AnimNotifyEvent.NotifyName == ReadyToCastAnimNotifyName) bIsReadyToCast = true;
	if (AnimNotifyEvent.NotifyName == FinishedCastingAnimNotifyName) bIsReadyToCast = false;
}
