// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability System/Demo/DemoInteractionAction.h"

#include "Ability System/Interactable.h"
#include "Kismet/KismetSystemLibrary.h"

bool UDemoInteractionAction::ExecuteActionImplementation_Implementation(const FActionParams& Params)
{
	FVector EyeLocation;
	FRotator EyeRotator;
	DemoCharacter->GetActorEyesViewPoint(EyeLocation, EyeRotator);

	const FVector TraceStart = EyeLocation;
	const FVector TraceEnd = EyeLocation + EyeRotator.Vector() * InteractionDistance;
	FHitResult Hit;
	UKismetSystemLibrary::LineTraceSingle(GetWorld(), TraceStart, TraceEnd, TraceChannel, false, ActorsToIgnore, TraceDrawDebugType, Hit, true, TraceColor, TraceHitColor, TraceDrawTime);

	if (!Hit.bBlockingHit) return false;

	AActor* HitActor = Hit.GetActor();

	if (!HitActor->Implements<UInteractable>()) return false;

	IInteractable::Execute_Interact(HitActor);

	return true;
}
