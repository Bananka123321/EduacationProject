#pragma once

#include "CoreMinimal.h"
#include "ItemActor.h" 
#include "ItemData.generated.h"

USTRUCT(BlueprintType)
struct FItemData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    TSubclassOf<class AItemActor> ItemClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    UStaticMesh* ItemMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    FVector ItemScale;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    FText ItemName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    FText ItemDescription;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
    FVector IconLocation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
    FVector IconScale;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
    float SphereRadius;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inspection")
    bool bInspect;

    FItemData()
        : ItemClass(nullptr),
        ItemMesh(nullptr),
        ItemScale(FVector(1.0f)),
        ItemName(FText::FromString("Default Name")),
        ItemDescription(FText::FromString("Default Description")),
        IconLocation(FVector(0.0f)),
        IconScale(FVector(1.0f)),
        SphereRadius(200.0f),
        bInspect(false)
    {
    }
};
