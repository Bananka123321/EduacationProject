// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InspectWidget.generated.h"

UCLASS()
class GRABITELI_API UInspectWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    // Открытые переменные для передачи данных
    UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
    FText ItemName;

    UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
    FText ItemDescription;

    // Функция для установки данных (вызывается из C++)
    UFUNCTION(BlueprintCallable)
    void InitializeWidget(const FText& NewName, const FText& NewDescription);
};
