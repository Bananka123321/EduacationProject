// Fill out your copyright notice in the Description page of Project Settings.

#include "GraphicsSettingsManager.h"
#include "SettingsManager.h"
#include "GameFramework/GameUserSettings.h"
#include "Engine/Engine.h"
#include "Scalability.h"
#include "Engine/RendererSettings.h"
#include "HAL/IConsoleManager.h"

void UGraphicsSettingsManager::Initialize()
{
    USettingsManager* SettingsMgr = USettingsManager::Get();

    SettingsMgr->OnApplyChanged.AddUObject(this, &UGraphicsSettingsManager::ApplyAllGraphicsSettings);

    ApplyAllGraphicsSettings();
}

void UGraphicsSettingsManager::ApplyAllGraphicsSettings()
{
    USettingsManager* SettingsMgr = USettingsManager::Get();
    if (!SettingsMgr) return;

    if (UGameUserSettings* Settings = GEngine->GetGameUserSettings())
    {
        Settings->SetViewDistanceQuality(SettingsMgr->GetInt("ViewDistance"));
        Settings->SetAntiAliasingQuality(SettingsMgr->GetInt("AntiAliasing"));
        Settings->SetShadowQuality(SettingsMgr->GetInt("Shadows"));
        Settings->SetPostProcessingQuality(SettingsMgr->GetInt("PostProcess"));
        Settings->SetTextureQuality(SettingsMgr->GetInt("Textures"));
        Settings->SetVisualEffectQuality(SettingsMgr->GetInt("Effects"));
        Settings->SetShadingQuality(SettingsMgr->GetInt("Shading"));
        Settings->SetGlobalIlluminationQuality(SettingsMgr->GetInt("GlobalIlluminations"));
        Settings->SetReflectionQuality(SettingsMgr->GetInt("Reflections"));
        Settings->SetVSyncEnabled(SettingsMgr->GetBool("VSync"));
        Settings->SetFrameRateLimit(SettingsMgr->GetFloat("FPS"));
        Settings->ApplySettings(false);
        Settings->SaveSettings();
    }

    //ApplyFloatSetting("MouseSensitivity", SettingsMgr->GetFloat("MouseSensitivity"));
    //ApplyFloatSetting("MasterVolume", SettingsMgr->GetFloat("MasterVolume"));
}


//void UGraphicsSettingsManager::OnSettingChanged(FName Key, int32 IntValue)
//{
//    if (UGameUserSettings* Settings = GEngine->GetGameUserSettings())
//    {
//        if (Key == "Shadows")           Settings->SetShadowQuality(IntValue);
//        else if (Key == "ViewDistance") Settings->SetViewDistanceQuality(IntValue);
//        else if (Key == "AntiAliasing") Settings->SetAntiAliasingQuality(IntValue);
//        else if (Key == "PostProcess")  Settings->SetPostProcessingQuality(IntValue);
//        else if (Key == "Textures")     Settings->SetTextureQuality(IntValue);
//        else if (Key == "Foliage")      Settings->SetFoliageQuality(IntValue);
//        else if (Key == "Shading")      Settings->SetShadingQuality(IntValue);
//
//        Settings->ApplySettings(false);
//        Settings->SaveSettings();
//    }
//}
//
//void UGraphicsSettingsManager::OnSettingChanged(FName Key, float FloatValue)
//{
//    ApplyFloatSetting(Key, FloatValue);
//}
//
//void UGraphicsSettingsManager::OnSettingChanged(FName Key, bool BoolValue)
//{
//    if (Key == "IsFullscreen")
//    {
//        if (UGameUserSettings* Settings = GEngine->GetGameUserSettings())
//        {
//            Settings->SetFullscreenMode(BoolValue ? EWindowMode::Fullscreen : EWindowMode::Windowed);
//            Settings->ApplySettings(false);
//        }
//    }
//}


void UGraphicsSettingsManager::ApplyIntCVar(const FString& CVarName, int32 Value)
{
    if (IConsoleVariable* CVar = IConsoleManager::Get().FindConsoleVariable(*CVarName))
    {
        CVar->Set(Value);
    }
}

void UGraphicsSettingsManager::ApplyFloatSetting(FName Key, float Value)
{
    if (Key == "MouseSensitivity")
    {
        UE_LOG(LogTemp, Log, TEXT("Apply MouseSensitivity: %f"), Value);
    }
    else if (Key == "MasterVolume")
    {
        UE_LOG(LogTemp, Log, TEXT("Apply MasterVolume: %f"), Value);
    }
}