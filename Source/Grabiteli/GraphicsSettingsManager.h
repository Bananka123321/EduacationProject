// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/RendererSettings.h"
#include "GraphicsSettingsManager.generated.h"

class USettingsManager;

UCLASS()
class GRABITELI_API UGraphicsSettingsManager : public UObject
{
    GENERATED_BODY()

public:
    void Initialize();

private:
    void ApplyAllGraphicsSettings();

    void OnSettingChanged(FName Key, int32 IntValue);
    void OnSettingChanged(FName Key, float FloatValue);
    void OnSettingChanged(FName Key, bool BoolValue);

    void ApplyIntCVar(const FString& CVarName, int32 Value);
    void ApplyFloatSetting(FName Key, float Value);
};
