#include "MyPlayerController.h"
#include "MainCharacter.h"

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (!InputComponent) return;

	InputComponent->BindAxis("MoveForward", this, &AMyPlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AMyPlayerController::MoveRight);
	InputComponent->BindAxis("LookUp", this, &AMyPlayerController::LookUp);
	InputComponent->BindAxis("Turn", this, &AMyPlayerController::Turn);

	InputComponent->BindAction("Run", IE_Pressed, this, &AMyPlayerController::StartRunning);
	InputComponent->BindAction("Run", IE_Released, this, &AMyPlayerController::StopRunning);
	InputComponent->BindAction("Crouch", IE_Pressed, this, &AMyPlayerController::StartCrouching);
	InputComponent->BindAction("Crouch", IE_Released, this, &AMyPlayerController::StopCrouching);

	InputComponent->BindAction("Interact", IE_Pressed, this, &AMyPlayerController::InteractWithItem);
	InputComponent->BindAction("Drop", IE_Pressed, this, &AMyPlayerController::DropCurrentItem);
	InputComponent->BindAction("SwitchSlot", IE_Pressed, this, &AMyPlayerController::SwitchInventorySlot);

}

void AMyPlayerController::BeginPlay() {
	Super::BeginPlay();
	UpdateController();
}
AMainCharacter* AMyPlayerController::GetControlledCharacter()
{
	return Cast<AMainCharacter>(GetPawn());
}

void AMyPlayerController::MoveForward(float Value)
{
	if (MyChar)
		MyChar->AddMovementInput(MyChar->GetActorForwardVector(), Value);
}

void AMyPlayerController::MoveRight(float Value)
{
	if (MyChar)
		MyChar->AddMovementInput(MyChar->GetActorRightVector(), Value);
}

void AMyPlayerController::LookUp(float Value)
{
	AddPitchInput(Value);
}

void AMyPlayerController::Turn(float Value)
{
	AddYawInput(Value);
}

void AMyPlayerController::StartRunning()
{
	if (bIsInspecting) return; 
	if (MyChar) MyChar->StartRunning();
}

void AMyPlayerController::StopRunning()
{
	if (bIsInspecting) return;
	if (MyChar) MyChar->StopRunning();
}

void AMyPlayerController::StartCrouching()
{
	if (bIsInspecting) return;
	if (MyChar) {
		MyChar->StartCrouching();
		MyChar->bWantsToCrouch = true;
	}
}

void AMyPlayerController::StopCrouching()
{
	if (bIsInspecting) return;
	if (MyChar) {
		MyChar->bWantsToCrouch = false;
		MyChar->StopCrouching();
	}
}

void AMyPlayerController::InteractWithItem()
{
	if (bIsInspecting) return;
	if (MyChar)MyChar->InteractWithItem();
}

void AMyPlayerController::DropCurrentItem()
{
	MyChar->DropCurrentItem();
}

void AMyPlayerController::SwitchInventorySlot()
{
	MyChar->SwitchInventorySlot();
}

void AMyPlayerController::UpdateController()
{
	MyChar = GetControlledCharacter();
}

void AMyPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	UpdateController();
}

