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
    // �������� ���������� ��� �������� ������
    UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
    FText ItemName;

    UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
    FText ItemDescription;

    // ������� ��� ��������� ������ (���������� �� C++)
    UFUNCTION(BlueprintCallable)
    void InitializeWidget(const FText& NewName, const FText& NewDescription);
};
