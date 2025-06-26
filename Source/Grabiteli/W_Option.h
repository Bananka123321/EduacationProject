// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SettingTypes.h"
#include "W_Option.generated.h"

class UTextBlock;
class UButton;
class USlider;

UCLASS()
class GRABITELI_API UW_Option : public UUserWidget
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Option")
    FName SettingsKey;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Option")
    ESettingValueType OptionValueType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn), Category = "Option")
    FText SettingsName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn), Category = "Option")
    TArray<FText> OptionValues;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    bool CurrentBoolValue = false;

    int32 CurrentIndex = 0;

    float CurrentFloatValue;
    

protected:
    virtual void NativeOnInitialized() override;

public:
    void LoadOption();
    void SaveOption();

    UFUNCTION(BlueprintCallable, Category = "MyFunctions")
    void SwitchButton();

    UFUNCTION()
    void SetValueText(float Value);

    UFUNCTION()
    void OnLeftClicked();

    UFUNCTION()
    void OnRightClicked();

    void RefreshVisual();

    UFUNCTION(BlueprintImplementableEvent, Category = "MyEvents")
    void UpdateButtons();

protected:
    UPROPERTY(meta = (BindWidget))
    UTextBlock* LabelText;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* ValueText;

    UPROPERTY(meta = (BindWidget))
    UButton* LeftButton;

    UPROPERTY(meta = (BindWidget))
    UButton* RightButton;

    UPROPERTY(meta = (BindWidget))
    USlider* Slider;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* SliderValueText;
};

