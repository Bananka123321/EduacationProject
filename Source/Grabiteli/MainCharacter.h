#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

// Forward declarations
class UInventoryComponent;
class UStaminaComponent;

UCLASS()
class GRABITELI_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMainCharacter();
	virtual void Tick(float DeltaTime) override;
	void LookUp(float Value);
	void Turn(float Value);
	void MoveForward(float Value);
	void MoveRight(float Value);

	void StartRunning();
	void StopRunning();
	void StartCrouching();
	void StopCrouching();
	bool CanUncrouch();

	void InteractWithItem();
	void DropCurrentItem();
	void SwitchInventorySlot();

	AActor* PerformTrace();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Crouch")
	bool bWantsToCrouch = false;

protected:

	virtual void BeginPlay() override;

private:
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Camera Component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;

	// Inventory Component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	UInventoryComponent* InventoryComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	UStaminaComponent* StaminaComponent;

	// Interaction range for item pickup
	UPROPERTY(EditDefaultsOnly, Category = "Interaction")
	float InteractionRange = 300.0f;

	UPROPERTY(EditAnywhere, Category = "Camera")
	float DefaultFOV = 90.0f;

	UPROPERTY(EditAnywhere, Category = "Camera")
	float RunningFOV = 100.0f;

	UPROPERTY(EditAnywhere, Category = "Camera")
	float FOVInterpSpeed = 5.0f;


	bool bIsRunning = false;

	void UpdateFOV(float DeltaTime);
};
