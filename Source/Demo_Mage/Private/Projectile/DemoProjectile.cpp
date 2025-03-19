// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/DemoProjectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"


// Sets default values
ADemoProjectile::ADemoProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!RootComponent) RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));

	SphereComponent->SetupAttachment(RootComponent);

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ADemoProjectile::ProjectileOverlapBeginHandler);

	ProjectileMovementComponent->SetUpdatedComponent(SphereComponent);
	ProjectileMovementComponent->InitialSpeed = 5000.0f;
	ProjectileMovementComponent->MaxSpeed = 5000.0f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->ProjectileGravityScale = 0.0f;

	InitialLifeSpan = 3.0f;
}

// Called when the game starts or when spawned
void ADemoProjectile::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ADemoProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADemoProjectile::Launch(const FVector& Direction) const
{
	ProjectileMovementComponent->Velocity = Direction * ProjectileMovementComponent->InitialSpeed;
}

void ADemoProjectile::ProjectileOverlapBeginHandler(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                                    const FHitResult& SweepResult)
{
	if (OtherActor == GetInstigator()) return;

	OnProjectileBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

void ADemoProjectile::OnProjectileBeginOverlap_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                                              const FHitResult& SweepResult)
{
}
