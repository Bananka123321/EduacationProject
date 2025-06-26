#include "InventoryComponent.h"
#include "ItemActor.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

UInventoryComponent::UInventoryComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
    ActiveSlot = 0;
}


void UInventoryComponent::BeginPlay()
{
    Super::BeginPlay();
    Inventory.SetNum(MaxSlots);
}

bool UInventoryComponent::AddItem(AItemActor* Item)
{
    if (!Item)
        return false;

    FItemData ItemData;
    ItemData.ItemClass = Item->GetClass();
    ItemData.ItemMesh = Item->GetItemMesh();
    ItemData.ItemScale = Item->GetItemScale();
    ItemData.ItemName = Item->GetItemName();
    ItemData.ItemDescription = Item->GetItemDescription();
    ItemData.IconLocation = Item->GetIconLocation();
    ItemData.IconScale = Item->GetIconScale();
    ItemData.bInspect = Item->GetbInspect();

    if (Inventory[ActiveSlot].ItemClass == nullptr)
    {
        Inventory[ActiveSlot] = ItemData;
        Item->Destroy();
        return true;
    }
    for (int32 i = 0; i < MaxSlots; i++)
    {
        if (Inventory[i].ItemClass == nullptr)
        {
            Inventory[i] = ItemData;
            Item->Destroy();
            return true;
        }
    }

    return false;
}

TSubclassOf<AItemActor> UInventoryComponent::GetActiveItem() const
{
    if (ActiveSlot >= 0 && ActiveSlot < MaxSlots && Inventory[ActiveSlot].ItemClass != nullptr)
    {
        return Inventory[ActiveSlot].ItemClass;
    }
    return nullptr;
}

void UInventoryComponent::SwitchItem(int32 NewSlotIndex)
{
    if (NewSlotIndex < 0 || NewSlotIndex >= MaxSlots)
        return;
    UE_LOG(LogTemp, Log, TEXT("Switched to slot %d. Item: %s"),
        NewSlotIndex,
        Inventory[NewSlotIndex].ItemClass != nullptr ? *Inventory[NewSlotIndex].ItemName.ToString() : TEXT("None"));


    ActiveSlot = NewSlotIndex;
}

void UInventoryComponent::DropItem(int32 SlotIndex)
{
    if (SlotIndex < 0 || SlotIndex >= MaxSlots || Inventory[SlotIndex].ItemClass == nullptr)
        return;

    if (CanDrop())
    {
        SpawnDroppedItem(Inventory[SlotIndex]);
        Inventory[SlotIndex] = FItemData();
    }
}


void UInventoryComponent::SpawnDroppedItem(const FItemData& ItemData)
{
    if (ItemData.ItemClass == nullptr)
        return;

    FVector DropLocation = GetOwner()->GetActorLocation() + GetOwner()->GetActorForwardVector() * 100.0f;
    FRotator DropRotation = FRotator::ZeroRotator;
    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

    AItemActor* SpawnedItem = GetWorld()->SpawnActor<AItemActor>(ItemData.ItemClass, DropLocation, DropRotation, SpawnParams);

    if (SpawnedItem)
    {
        SpawnedItem->SetItemMesh(ItemData.ItemMesh);
        SpawnedItem->SetSphereRadius(ItemData.SphereRadius);
        SpawnedItem->SetIconScale(ItemData.IconScale);
        SpawnedItem->SetItemScale(ItemData.ItemScale);
        SpawnedItem->SetItemName(ItemData.ItemName);
        SpawnedItem->SetItemDescription(ItemData.ItemDescription);
        SpawnedItem->SetIconLocation(ItemData.IconLocation);
        SpawnedItem->SetbInspect(ItemData.bInspect);
        SpawnedItem->SetupIcons();
        SpawnedItem->StaticMesh->SetSimulatePhysics(true);
    }
}

bool UInventoryComponent::CanDrop()
{
    FVector DropLocation = GetOwner()->GetActorLocation() + GetOwner()->GetActorForwardVector() * 200.0f;
    FHitResult HitResult;
    FCollisionQueryParams Params;
    Params.AddIgnoredActor(GetOwner());

    bool bObstacle = GetWorld()->LineTraceSingleByChannel(
        HitResult,
        GetOwner()->GetActorLocation(),
        DropLocation,
        ECC_Visibility,
        Params);

    return !bObstacle;
}