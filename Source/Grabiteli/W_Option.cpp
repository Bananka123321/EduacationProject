#include "W_Option.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/Slider.h"
#include "SettingsManager.h"

void UW_Option::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    if (Slider && !Slider->OnValueChanged.IsAlreadyBound(this, &UW_Option::SetValueText))
        Slider->OnValueChanged.AddDynamic(this, &UW_Option::SetValueText);
    if (LeftButton && !LeftButton->OnClicked.IsAlreadyBound(this, &UW_Option::OnLeftClicked))
        LeftButton->OnClicked.AddDynamic(this, &UW_Option::OnLeftClicked);
    if (RightButton && !RightButton->OnClicked.IsAlreadyBound(this, &UW_Option::OnRightClicked))
        RightButton->OnClicked.AddDynamic(this, &UW_Option::OnRightClicked);
    if (LabelText)
        LabelText->SetText(SettingsName);
}


void UW_Option::LoadOption()
{
    USettingsManager* Mgr = USettingsManager::Get();
    if (!Mgr) return;

    switch (OptionValueType)
    {
    case ESettingValueType::Int:
        CurrentIndex = Mgr->GetInt(SettingsKey);
        break;
    case ESettingValueType::Float:
        CurrentFloatValue = Mgr->GetFloat(SettingsKey);
        break;
    case ESettingValueType::Bool:
        CurrentBoolValue = Mgr->GetBool(SettingsKey);
        break;
    }

    RefreshVisual();
}

void UW_Option::SaveOption()
{
    USettingsManager* Mgr = USettingsManager::Get();
    if (!Mgr) return;

    switch (OptionValueType)
    {
    case ESettingValueType::Int:
        Mgr->SetInt(SettingsKey, CurrentIndex);
        break;
    case ESettingValueType::Float:
        Mgr->SetFloat(SettingsKey, CurrentFloatValue);
        break;
    case ESettingValueType::Bool:
        Mgr->SetBool(SettingsKey, CurrentBoolValue);
        break;
    }
}

void UW_Option::OnLeftClicked()
{
    if (OptionValueType == ESettingValueType::Int && CurrentIndex > 0)
    {
        CurrentIndex--;
        RefreshVisual();
    }
}

void UW_Option::OnRightClicked()
{
    if (OptionValueType == ESettingValueType::Int && CurrentIndex < OptionValues.Num() - 1)
    {
        CurrentIndex++;
        RefreshVisual();
    }
}

void UW_Option::SetValueText(float Value)
{
    if (Value > 240)
    {
        SliderValueText->SetText(FText::FromString(TEXT("Unlimited")));
        CurrentFloatValue = 999;
    }
    else {
        CurrentFloatValue = Value;
        int32 TruncatedValue = FMath::TruncToInt(Value);
        FString ValueString = FString::Printf(TEXT("%d"), TruncatedValue);
        SliderValueText->SetText(FText::FromString(ValueString));
    }
}

void UW_Option::RefreshVisual()
{
    if (OptionValueType == ESettingValueType::Int && ValueText && OptionValues.IsValidIndex(CurrentIndex))
    {
        ValueText->SetText(OptionValues[CurrentIndex]);
    }
    
    if (LeftButton)
        LeftButton->SetVisibility((OptionValueType == ESettingValueType::Int && CurrentIndex > 0)
            ? ESlateVisibility::Visible : ESlateVisibility::Hidden);

    if (RightButton)
        RightButton->SetVisibility((OptionValueType == ESettingValueType::Int && CurrentIndex < OptionValues.Num() - 1)
            ? ESlateVisibility::Visible : ESlateVisibility::Hidden);

    //======================================================================================================================

    if (Slider)
    {
        Slider->SetValue(CurrentFloatValue);
        SetValueText(CurrentFloatValue);
    }

    //======================================================================================================================

    UpdateButtons();
}

void UW_Option::SwitchButton() {
    CurrentBoolValue = !CurrentBoolValue;
}