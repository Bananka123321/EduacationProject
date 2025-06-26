#include "SettingsManager.h"
#include "Kismet/GameplayStatics.h"

USettingsManager* USettingsManager::Get()
{
    static USettingsManager* Instance = nullptr;
    if (!Instance)
    {
        Instance = NewObject<USettingsManager>();
        Instance->AddToRoot();
        Instance->LoadSettings();
    }
    return Instance;
}

void USettingsManager::LoadSettings()
{
    if (UGameplayStatics::DoesSaveGameExist(SlotName, 0))
    {
        SettingsData = Cast<USaveSettings>(
            UGameplayStatics::LoadGameFromSlot(SlotName, 0));
    }
    if (!SettingsData)
    {
        SettingsData = Cast<USaveSettings>(
            UGameplayStatics::CreateSaveGameObject(USaveSettings::StaticClass()));
    }
}

void USettingsManager::SaveSettings()
{
    if (SettingsData)
    {
        UGameplayStatics::SaveGameToSlot(SettingsData, SlotName, 0);
        OnApplyChanged.Broadcast();
    }
}

int32 USettingsManager::GetInt(FName Key) const
{
    if (!SettingsData) return 0;
    const int32* Found = SettingsData->IntSettings.Find(Key);
    return Found ? *Found : 0;
}

float USettingsManager::GetFloat(FName Key) const
{
    if (!SettingsData) return 0.f;
    const float* Found = SettingsData->FloatSettings.Find(Key);
    return Found ? *Found : 0.f;
}

bool USettingsManager::GetBool(FName Key) const
{
    if (!SettingsData) return false;
    const bool* Found = SettingsData->BoolSettings.Find(Key);
    return Found ? *Found : false;
}

void USettingsManager::SetInt(FName Key, int32 Value)
{
    if (!SettingsData) return;

    SettingsData->IntSettings.FindOrAdd(Key) = Value;
}

void USettingsManager::SetFloat(FName Key, float Value)
{
    if (!SettingsData) return;

    SettingsData->FloatSettings.FindOrAdd(Key) = Value;
}

void USettingsManager::SetBool(FName Key, bool Value)
{
    if (!SettingsData) return;

    SettingsData->BoolSettings.FindOrAdd(Key) = Value;
}