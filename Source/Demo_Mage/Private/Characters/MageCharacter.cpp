// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/MageCharacter.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "InputAction.h"


// Sets default values
AMageCharacter::AMageCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh"));

	CameraComponent->SetupAttachment(RootComponent);
	SkeletalMeshComponent->SetupAttachment(CameraComponent);

	CameraComponent->bUsePawnControlRotation = true;

	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

// Called when the game starts or when spawned
void AMageCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMageCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMageCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	const APlayerController* PlayerController = Cast<APlayerController>(GetController());
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(InputMappingContext.LoadSynchronous(), 0);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	EnhancedInputComponent->BindAction(MoveAction.LoadSynchronous(), ETriggerEvent::Triggered, this, &AMageCharacter::MoveInputCallback);
	EnhancedInputComponent->BindAction(SprintAction.LoadSynchronous(), ETriggerEvent::Triggered, this, &AMageCharacter::SprintInputCallback);
	EnhancedInputComponent->BindAction(JumpAction.LoadSynchronous(), ETriggerEvent::Triggered, this, &AMageCharacter::JumpInputCallback);
	EnhancedInputComponent->BindAction(CameraMovementAction.LoadSynchronous(), ETriggerEvent::Triggered, this, &AMageCharacter::CameraMovementInputCallback);
	EnhancedInputComponent->BindAction(BasicAttackAction.LoadSynchronous(), ETriggerEvent::Triggered, this, &AMageCharacter::BasicAttackInputCallback);
	EnhancedInputComponent->BindAction(SelectAbilityAction.LoadSynchronous(), ETriggerEvent::Triggered, this, &AMageCharacter::SelectAbilityInputCallback);
	EnhancedInputComponent->BindAction(AbilityAction.LoadSynchronous(), ETriggerEvent::Triggered, this, &AMageCharacter::AbilityActionInputCallback);
}

void AMageCharacter::MoveInputCallback(const FInputActionValue& Value)
{
	const FVector2D Direction = Value.Get<FVector2D>();
	if (Direction.X != 0)
	{
		AddMovementInput(GetActorForwardVector() * Direction.X);
	}

	if (Direction.Y != 0)
	{
		AddMovementInput(GetActorRightVector() * Direction.Y);
	}
}

void AMageCharacter::SprintInputCallback(const FInputActionValue& Value)
{
	const bool ShouldSprint = Value.Get<bool>();

	GetCharacterMovement()->MaxWalkSpeed = ShouldSprint ? SprintSpeed : WalkSpeed;
}

void AMageCharacter::JumpInputCallback(const FInputActionValue& Value)
{
	Jump();
}

void AMageCharacter::CameraMovementInputCallback(const FInputActionValue& Value)
{
	const FVector2D CameraValue = Value.Get<FVector2D>();
	if (CameraValue == FVector2D::Zero()) return;

	APlayerController* PlayerController = Cast<APlayerController>(GetController());

	if (CameraValue.Y != 0)
		PlayerController->AddPitchInput(-CameraValue.Y);

	if (CameraValue.X != 0)
		PlayerController->AddYawInput(CameraValue.X);
}

void AMageCharacter::BasicAttackInputCallback(const FInputActionValue& Value)
{
	const bool ShouldAttack = Value.Get<bool>();
	ShouldAttack ? AbilityComponent->StartActionByName(TEXT("Basic Attack")) : AbilityComponent->StopActionByName(TEXT("Basic Attack")); // TODO: Refactor hard-coded names.
}

void AMageCharacter::SelectAbilityInputCallback(const FInputActionValue& Value)
{
	const int AbilityIndex = static_cast<int>(Value.Get<float>());
	AbilityComponent->ExecuteActionByName(TEXT("Select Ability"), FActionParams{AbilityIndex});
}

void AMageCharacter::AbilityActionInputCallback(const FInputActionValue& Value)
{
	const bool UseAbility = Value.Get<bool>();
	UE_LOG(LogTemp, Warning, TEXT("The boolean value is %s"), ( UseAbility ? TEXT("true"): TEXT("false") ));
	if (UseAbility)
		AbilityComponent->StartActionByName("Selected Ability");
	else

		AbilityComponent->StopActionByName("Selected Ability");
}
