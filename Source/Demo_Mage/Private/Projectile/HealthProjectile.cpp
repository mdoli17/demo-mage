// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/HealthProjectile.h"

#include "Attribute System/AttributeComponent.h"

AHealthProjectile::AHealthProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AHealthProjectile::OnProjectileBeginOverlap_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                                                const FHitResult& SweepResult)
{
	Super::OnProjectileBeginOverlap_Implementation(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	if (!OtherActor->Implements<UHealthComponentProvider>()) return;

	IHealthComponentProvider* HealthComponentProvider = Cast<IHealthComponentProvider>(OtherActor);
	UAttributeComponent* HealthComponent = HealthComponentProvider->GetHealthComponent();
	HealthComponent->SingleUse(HealthModifyAmount);
}
