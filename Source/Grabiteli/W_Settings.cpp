#include "W_Settings.h"
#include "W_Option.h"
#include "SettingsManager.h"
#include "Blueprint/WidgetTree.h"

void UW_Settings::NativeConstruct()
{
    Super::NativeConstruct();

    TArray<UWidget*> AllWidgets;
    WidgetTree->GetAllWidgets(AllWidgets);

    for (UWidget* Widget : AllWidgets)
    {
        if (UW_Option* Option = Cast<UW_Option>(Widget))
        {
            AllOptions.Add(Option);
        }
    }

    USettingsManager::Get()->LoadSettings();
    for (UW_Option* Opt : AllOptions)
    {
        if (Opt) Opt->LoadOption();
    }
}

void UW_Settings::SaveAll()
{
    for (UW_Option* Opt : AllOptions)
    {
        if (Opt) Opt->SaveOption();
    }
    USettingsManager::Get()->SaveSettings();
}
