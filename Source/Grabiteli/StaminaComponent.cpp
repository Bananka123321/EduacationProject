#include "StaminaComponent.h"
#include "TimerManager.h"

UStaminaComponent::UStaminaComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	CurrentStamina = MaxStamina;
}

void UStaminaComponent::BeginPlay()
{
	Super::BeginPlay();
}

bool UStaminaComponent::CanRun() const
{
	return (CurrentStamina > 0.0f) and (Canrun);
}

void UStaminaComponent::ConsumeStamina(float DeltaTime)
{
	CurrentStamina = FMath::Clamp(CurrentStamina - StaminaDrainRate * DeltaTime, 0.0f, MaxStamina);

	if (CurrentStamina <= 0.0f)
	{
		Canrun = false;
		StartRegenTimer();
	}
}


void UStaminaComponent::RegenerateStamina()
{
	bCanRegenerate = true;

	if (CurrentStamina < MaxStamina)
	{
		GetWorld()->GetTimerManager().SetTimer(RegenTimerHandle, this, &UStaminaComponent::RegenerateStamina, 0.1f, true);
		CurrentStamina = FMath::Clamp(CurrentStamina + StaminaRegenRate * 0.1f, 0.0f, MaxStamina);

		if (CurrentStamina == MaxStamina)
		{
			Canrun = true;
			GetWorld()->GetTimerManager().ClearTimer(RegenTimerHandle);
		}
	}
}

void UStaminaComponent::StartRegenTimer()
{
	bCanRegenerate = false;
	GetWorld()->GetTimerManager().ClearTimer(RegenTimerHandle);
	GetWorld()->GetTimerManager().SetTimer(RegenTimerHandle, this, &UStaminaComponent::RegenerateStamina, StaminaRegenDelay, false);
}