#include "MainCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/InputComponent.h"
#include "InventoryComponent.h"
#include "StaminaComponent.h"
#include "ItemActor.h"
#include "InteractionInterface.h"
#include "Components/CapsuleComponent.h"
#include "DrawDebugHelpers.h"

AMainCharacter::AMainCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(RootComponent);
	CameraComponent->bUsePawnControlRotation = true;

	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));
	StaminaComponent = CreateDefaultSubobject<UStaminaComponent>(TEXT("StaminaComponent"));

	GetCharacterMovement()->MaxWalkSpeed = 300.0f;
	GetCharacterMovement()->MaxWalkSpeedCrouched = 150.0f;
	GetCharacterMovement()->NavAgentProps.bCanCrouch = true;
}

void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	CameraComponent->FieldOfView = DefaultFOV;
}

void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateFOV(DeltaTime);

	if (bIsRunning && StaminaComponent->CanRun())
	{
		StaminaComponent->ConsumeStamina(DeltaTime);

		if (!StaminaComponent->CanRun())
		{
			StopRunning();
		}
	}
	if (!bWantsToCrouch && bIsCrouched && CanUncrouch()) 
		StopCrouching();
}

void AMainCharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value);
}

void AMainCharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector(), Value);
}

void AMainCharacter::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}

void AMainCharacter::Turn(float Value)
{
	AddControllerYawInput(Value);
}

void AMainCharacter::StartRunning()
{
	if (StaminaComponent->CanRun() && !GetCharacterMovement()->IsCrouching())
	{
		bIsRunning = true;
		GetCharacterMovement()->MaxWalkSpeed = 500.0f;
	}
}

void AMainCharacter::StopRunning()
{
	bIsRunning = false;
	GetCharacterMovement()->MaxWalkSpeed = 300.0f;
}

void AMainCharacter::StartCrouching()
{
	if (!bIsCrouched)
	{
		Crouch();
		bIsCrouched = true;
		FVector NewLocation = CameraComponent->GetComponentLocation();
		NewLocation.Z -= 45.0f;
		CameraComponent->SetWorldLocation(NewLocation);
		GetCapsuleComponent()->SetCapsuleHalfHeight(44);
	}
}

void AMainCharacter::StopCrouching()
{
	if (CanUncrouch() && bIsCrouched)
	{
		bIsCrouched = false;
		UnCrouch();
		FVector NewRelLocation = CameraComponent->GetRelativeLocation();
		NewRelLocation.Z += 45.0f;
		CameraComponent->SetRelativeLocation(NewRelLocation);
		GetCapsuleComponent()->SetCapsuleHalfHeight(88);
	}
}

bool AMainCharacter::CanUncrouch()
{
	UCapsuleComponent* Capsule = GetCapsuleComponent();
	if (!Capsule) return false;

	float StandingHalfHeight = Capsule->GetUnscaledCapsuleHalfHeight();
	float CapsuleRadius = Capsule->GetUnscaledCapsuleRadius();

	FVector CapsuleCenter = GetActorLocation() + FVector(0, 0, StandingHalfHeight);

	FCollisionShape StandingCapsule = FCollisionShape::MakeCapsule(CapsuleRadius, 88);

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	bool bBlocked = GetWorld()->OverlapBlockingTestByChannel(CapsuleCenter, FQuat::Identity, ECC_Visibility, StandingCapsule, QueryParams);

	return !bBlocked;
}

void AMainCharacter::UpdateFOV(float DeltaTime)
{
	float TargetFOV = bIsRunning ? RunningFOV : DefaultFOV;
	CameraComponent->FieldOfView = FMath::FInterpTo(CameraComponent->FieldOfView, TargetFOV, DeltaTime, FOVInterpSpeed);
}

void AMainCharacter::InteractWithItem()
{
	AActor* HitActor = PerformTrace();

	if (HitActor && HitActor->GetClass()->ImplementsInterface(UInteractionInterface::StaticClass()))
		IInteractionInterface::Execute_Interaction(HitActor, this);
}

void AMainCharacter::DropCurrentItem()
{
	if (InventoryComponent)
	{
		int32 ActiveSlotIndex = InventoryComponent->GetActiveSlotIndex();
		InventoryComponent->DropItem(ActiveSlotIndex);
	}
}

void AMainCharacter::SwitchInventorySlot()
{
	if (InventoryComponent)
	{
		int32 CurrentSlot = InventoryComponent->GetActiveSlotIndex();
		int32 NewSlot = (CurrentSlot + 1) % 4;
		InventoryComponent->SwitchItem(NewSlot);
	}
}

AActor* AMainCharacter::PerformTrace()
{
	FVector Start = CameraComponent->GetComponentLocation();
	FVector End = Start + CameraComponent->GetForwardVector() * InteractionRange;

	FHitResult HitResult;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, Params);

	return bHit ? HitResult.GetActor() : nullptr;
}
