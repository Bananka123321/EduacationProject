// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SaveSettings.generated.h"

/**
 * 
 */
UCLASS()
class GRABITELI_API USaveSettings : public USaveGame
{
	GENERATED_BODY()

public:
    UPROPERTY(VisibleAnywhere, Category = "Settings")
    TMap<FName, int32> IntSettings;

    UPROPERTY(VisibleAnywhere, Category = "Settings")
    TMap<FName, float> FloatSettings;

    UPROPERTY(VisibleAnywhere, Category = "Settings")
    TMap<FName, bool> BoolSettings;
};
