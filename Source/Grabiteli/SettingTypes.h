// SettingsTypes.h
#pragma once

#include "CoreMinimal.h"
#include "SettingTypes.generated.h"

UENUM(BlueprintType)
enum class ESettingValueType : uint8
{
    Int     UMETA(DisplayName = "Integer"),
    Float   UMETA(DisplayName = "Float"),
    Bool    UMETA(DisplayName = "Boolean")
};

USTRUCT(BlueprintType)
struct FSettingValue
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
    FName Key;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
    ESettingValueType Type;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
    int32 IntValue;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
    float FloatValue;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
    bool BoolValue;

    FSettingValue()
        : Key(NAME_None)
        , Type(ESettingValueType::Int)
        , IntValue(0)
        , FloatValue(0.f)
        , BoolValue(false)
    {
    }

    int32 GetInt()   const { return IntValue; }
    float GetFloat() const { return FloatValue; }
    bool GetBool()   const { return BoolValue; }

    void SetInt(int32 NewValue) { IntValue = NewValue;    Type = ESettingValueType::Int; }
    void SetFloat(float NewValue) { FloatValue = NewValue;  Type = ESettingValueType::Float; }
    void SetBool(bool NewValue) { BoolValue = NewValue;   Type = ESettingValueType::Bool; }
};
