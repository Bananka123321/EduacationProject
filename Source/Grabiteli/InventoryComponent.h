#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ItemData.h"
#include "InventoryComponent.generated.h"

class AItemActor;

UCLASS(Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GRABITELI_API UInventoryComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UInventoryComponent();

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    int32 GetActiveSlotIndex() const { return ActiveSlot; }

    bool AddItem(AItemActor* Item);

    void DropItem(int32 SlotIndex);

    TSubclassOf<AItemActor> GetActiveItem() const;

    void SwitchItem(int32 NewSlotIndex);
 
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
    TArray<FItemData> Inventory;

    UFUNCTION(BlueprintImplementableEvent, Category = "MyEvents")
    void ShowItemName();

protected:
    virtual void BeginPlay() override;

private:

    UPROPERTY(EditDefaultsOnly, Category = "Inventory")
    int32 MaxSlots = 4;

    int32 ActiveSlot;

    void SpawnDroppedItem(const FItemData& ItemData);

    bool CanDrop();
};
