// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_Settings.generated.h"


class UW_Option;

UCLASS()
class GRABITELI_API UW_Settings : public UUserWidget
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Settings")
    void SaveAll();

protected:
    UPROPERTY(meta = (BindWidgetOptional))
    TArray<UW_Option*> AllOptions;


    virtual void NativeConstruct() override;
};
