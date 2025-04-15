// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability System/Demo/MageBeamAction.h"

void UMageBeamAction::Initialize_Implementation()
{
	Super::Initialize_Implementation();

	DemoCharacter = Cast<ADemoCharacter>(Owner);
	ensure(DemoCharacter);
	AnimInterface = Cast<IDemoCharacterToAnimInterface>(DemoCharacter->GetSkeletalMesh()->GetAnimInstance());
	ensure(AnimInterface);

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

FVector UMageBeamAction::GetTraceStart_Implementation()
{
	FVector EyeLocation;
	FRotator EyeRotation;
	DemoCharacter->GetActorEyesViewPoint(EyeLocation, EyeRotation);

	return EyeLocation;
}

FVector UMageBeamAction::GetTraceEnd_Implementation()
{
	FVector EyeLocation;
	FRotator EyeRotation;
	DemoCharacter->GetActorEyesViewPoint(EyeLocation, EyeRotation);

	return EyeLocation + EyeRotation.Vector() * MaxVisionDistance;
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
