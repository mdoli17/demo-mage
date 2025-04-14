// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability System/BeamAction.h"

#include "Ability System/Beam/Beamable.h"
#include "Kismet/KismetSystemLibrary.h"

void UBeamAction::Tick(float DeltaTime)
{
	if (!bCanBeam) return;

	const FVector TraceStart = Caster ? IBeamCaster::Execute_GetBeamStart(Caster) : GetTraceStart();
	const FVector TraceEnd = Caster ? IBeamCaster::Execute_GetBeamEnd(Caster) : GetTraceEnd();

	FHitResult Hit;
	UKismetSystemLibrary::SphereTraceSingleForObjects(GetWorld(), TraceStart, TraceEnd, SphereTraceRadius, TraceObjectTypes, false, ActorsToIngoreDuringTrace, TraceDrawDebugType, Hit, true,
	                                                  TraceColor, TraceHitColor, TraceDrawTime);

	if (!Hit.bBlockingHit)
	{
		if (TracedActor)
		{
			if (TracedActor->Implements<UBeamable>())
			{
				IBeamable::Execute_StopHandlingBeam(TracedActor);
				TracedActor = nullptr;
			}
		}
		return;
	}

	AActor* HitActor = Hit.GetActor();

	// Check new target
	if (HitActor != TracedActor)
	{
		if (TracedActor)
		{
			if (TracedActor->Implements<UBeamable>())
			{
				IBeamable::Execute_StopHandlingBeam(TracedActor);
			}
		}

		TracedActor = HitActor;
		if (TracedActor->Implements<UBeamable>())
		{
			IBeamable::Execute_StartHandlingBeam(TracedActor, Hit);
		}
	}
	else
	{
		if (TracedActor->Implements<UBeamable>())
		{
			IBeamable::Execute_UpdateHandlingBeam(TracedActor, Hit);
		}
	}
}

void UBeamAction::Initialize_Implementation()
{
	ActorsToIngoreDuringTrace.Add(Owner);
	if (Owner->Implements<UBeamCaster>())
	{
		Caster = Owner;
	}
}

bool UBeamAction::StartActionImplementation_Implementation(const FActionParams& Params)
{
	bCanBeam = true;
	return true;
}

bool UBeamAction::StopActionImplementation_Implementation()
{
	bCanBeam = false;

	if (TracedActor)
	{
		if (TracedActor->Implements<UBeamable>())
		{
			IBeamable::Execute_StopHandlingBeam(TracedActor);
			TracedActor = nullptr;
		}
	}

	return true;
}

FVector UBeamAction::GetTraceEnd_Implementation()
{
	return GetTraceStart() + Owner->GetActorForwardVector();
}

FVector UBeamAction::GetTraceStart_Implementation()
{
	return Owner->GetActorLocation();
}
