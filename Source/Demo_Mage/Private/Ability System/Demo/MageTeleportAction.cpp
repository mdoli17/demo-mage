// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability System/Demo/MageTeleportAction.h"

#include "Kismet/KismetSystemLibrary.h"

void UMageTeleportAction::Initialize_Implementation()
{
	Super::Initialize_Implementation();
	ActorsToIgnoreDuringTrace.Add(Owner);

	AnimInterface->GetAnimNotifyEventReceived().AddDynamic(this, &UMageTeleportAction::AnimNotifyEventReceivedHandler);
}

bool UMageTeleportAction::StartActionImplementation_Implementation(const FActionParams& Params)
{
	if (const bool TargetFound = SetupInitialTarget(); !TargetFound)
	{
		// TODO: Handle fail effects.
		ResetTargets();
		return false;
	}

	AnimInterface->StartAbility();
	OnCastStarted();
	return Super::StartActionImplementation_Implementation(Params);
}

bool UMageTeleportAction::StopActionImplementation_Implementation()
{
	if (const bool TargetFound = SetupFinalTarget(); !TargetFound)
	{
		ResetTargets();
		AnimInterface->StopAbility(false);
		OnCastFailed();
		return true; // Returning true so that ability stops.
	}

	AnimInterface->StopAbility();
	OnCastSucceeded();
	return Super::StopActionImplementation_Implementation();
}

void UMageTeleportAction::AnimNotifyEventReceivedHandler(const FAnimNotifyEvent& AnimNotifyEvent)
{
	if (AnimNotifyEvent.NotifyName != AnimNotifyName) return;

	TeleportTargets();
	ResetTargets();
}

bool UMageTeleportAction::SetupInitialTarget()
{
	FHitResult Hit;
	SphereTrace(Hit);

	InitialTarget = Hit.bBlockingHit ? Hit.GetActor() : nullptr;

	return Hit.bBlockingHit;
}

bool UMageTeleportAction::SetupFinalTarget()
{
	FHitResult Hit;
	SphereTrace(Hit);

	FinalTarget = Hit.bBlockingHit ? Hit.GetActor() : nullptr;

	return Hit.bBlockingHit && FinalTarget != InitialTarget;
}

void UMageTeleportAction::TeleportTargets() const
{
	if (!InitialTarget || !FinalTarget || InitialTarget == FinalTarget) return;

	const FVector InitialPosition = InitialTarget->GetActorLocation();
	const FVector FinalPosition = FinalTarget->GetActorLocation();

	InitialTarget->SetActorLocation(FinalPosition, false, nullptr, ETeleportType::TeleportPhysics);
	FinalTarget->SetActorLocation(InitialPosition, false, nullptr, ETeleportType::TeleportPhysics);
}

void UMageTeleportAction::SphereTrace(FHitResult& Hit) const
{
	FVector EyesViewPointLocation;
	FRotator EyesViewPointRotation;
	DemoCharacter->GetActorEyesViewPoint(EyesViewPointLocation, EyesViewPointRotation);

	const FVector SphereStart = EyesViewPointLocation;
	const FVector SphereEnd = EyesViewPointLocation + EyesViewPointRotation.Vector() * MaxVisionDistance;

	UKismetSystemLibrary::SphereTraceSingleForObjects(GetWorld(), SphereStart, SphereEnd, SphereTraceRadius, TraceObjectTypes, false, ActorsToIgnoreDuringTrace, TraceDrawDebugType, Hit, true,
	                                                  TraceColor, TraceHitColor, TraceDrawTime);
}
