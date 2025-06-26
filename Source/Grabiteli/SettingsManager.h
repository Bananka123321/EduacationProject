// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SaveSettings.h"
#include "SettingsManager.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnApplyChanged);

UCLASS(Blueprintable)
class GRABITELI_API USettingsManager : public UObject
{
	GENERATED_BODY()
	
private:
    UPROPERTY()
    USaveSettings* SettingsData;

    FString SlotName = TEXT("UserSettings");

public:
    static USettingsManager* Get();

    void LoadSettings();
    void SaveSettings();

    int32 GetInt(FName Key)    const;
    void SetInt(FName Key, int32 Value);

    float GetFloat(FName Key)  const;
    void SetFloat(FName Key, float Value);

    bool GetBool(FName Key)   const;
    void SetBool(FName Key, bool Value);

    FOnApplyChanged OnApplyChanged;
};
