// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractionInterface.h"
#include "InspectWidget.h"
#include "MyPlayerController.h"
#include "Components/SceneCaptureComponent2D.h"
#include "InspectItem.generated.h"

UCLASS()
class GRABITELI_API AInspectItem : public AActor, public IInteractionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInspectItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	UStaticMesh* ItemMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector ItemScale;

	// Класс виджета для отображения
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UInspectWidget> InspectWidgetClass;

	// Указатель на сам созданный виджет
	UPROPERTY()
	UInspectWidget* InspectWidgetInstance;

	bool bRotate = false;
	float RotationSpeed = 3.0f;

	void OnLeftMousePressed();
	void OnLeftMouseReleased();
	void ResetRotation();

	UFUNCTION()
	void RotateItemX(float Value);

	UFUNCTION()
	void RotateItemY(float Value);

	void ZoomItem(float Value);

	bool bHadTurnBinding;
	bool bHadLookUpBinding;

	void Exit();

public:
	AMainCharacter* MyCharacter;
	AMyPlayerController* PC;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void Inspection_Implementation(AMainCharacter* Character, const FText& ItemName, const FText& ItemDescription) override;


	void SetItemMesh(UStaticMesh* NewMesh) { ItemMesh = NewMesh; StaticMesh->SetStaticMesh(ItemMesh); }
	void SetItemScale(FVector NewItemScale) { ItemScale = NewItemScale; StaticMesh->SetWorldScale3D(ItemScale); }

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Capture")
	USceneCaptureComponent2D* CaptureComponent;

	// Добавляем переменную для заранее подготовленного RenderTarget
	UPROPERTY()
	UTextureRenderTarget2D* PreconfiguredRenderTarget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FRotator Rotator;

};
