#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

UCLASS()
class GRABITELI_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;

	void MoveForward(float Value);
	void MoveRight(float Value);
	void LookUp(float Value);
	void Turn(float Value);
	void StartRunning();
	void StopRunning();
	void StartCrouching();
	void StopCrouching();
	void InteractWithItem();
	void DropCurrentItem();
	void SwitchInventorySlot();

	class AMainCharacter* GetControlledCharacter();
public:
	UFUNCTION(BlueprintCallable, Category = "MyCustomFunctions")
	void UpdateController();
	AMainCharacter* MyChar;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inspection")
	bool bIsInspecting = false;

};
