// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability System/Demo/MageTeleportAction.h"

#include "Kismet/KismetSystemLibrary.h"

void UMageTeleportAction::Initialize_Implementation()
{
	Super::Initialize_Implementation();
	ActorsToIgnoreDuringTrace.Add(Owner);
}

bool UMageTeleportAction::StartActionImplementation_Implementation(const FActionParams& Params)
{
	if (const bool TargetFound = SetupInitialTarget(); !TargetFound) return false;

	AnimInterface->StartAbility();
	return Super::StartActionImplementation_Implementation(Params);
}

bool UMageTeleportAction::StopActionImplementation_Implementation()
{
	AnimInterface->StopAbility();
	SetupFinalTarget();
	return Super::StopActionImplementation_Implementation();
}

bool UMageTeleportAction::SetupInitialTarget()
{
	FHitResult Hit;
	SphereTrace(Hit);
	// Sphere Trace
	// Get Initial Object or Initial Location

	return Hit.bBlockingHit;
}

void UMageTeleportAction::SetupFinalTarget()
{
	FHitResult Hit;
	SphereTrace(Hit);
	// Sphere Trace
	// Get Target Object or Target Location
}

void UMageTeleportAction::Teleport()
{
	// If Initial and Target Objects are valid, swap places
	// If Initial Target Object is available, teleport to Target Location
	// If Target Object is available, teleport to Initial Location
}

void UMageTeleportAction::SphereTrace(FHitResult& Hit)
{
	FVector EyesViewPointLocation;
	FRotator EyesViewPointRotation;
	DemoCharacter->GetActorEyesViewPoint(EyesViewPointLocation, EyesViewPointRotation);

	const FVector SphereStart = EyesViewPointLocation;
	const FVector SphereEnd = EyesViewPointLocation + EyesViewPointRotation.Vector() * MaxVisionDistance;

	UKismetSystemLibrary::SphereTraceSingleForObjects(GetWorld(), SphereStart, SphereEnd, SphereTraceRadius, TraceObjectTypes, false, ActorsToIgnoreDuringTrace, TraceDrawDebugType, Hit, true,
	                                                  TraceColor, TraceHitColor, TraceDrawTime);
}
