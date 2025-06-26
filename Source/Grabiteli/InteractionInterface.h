#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MainCharacter.h"
#include "InteractionInterface.generated.h"

UINTERFACE(MinimalAPI)
class UInteractionInterface : public UInterface
{
    GENERATED_BODY()
};

class GRABITELI_API IInteractionInterface
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interaction")
    void Interaction(AMainCharacter* Character);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interaction")
    void Inspection(AMainCharacter* Character, const FText& ItemName, const FText& ItemDescription);
};
