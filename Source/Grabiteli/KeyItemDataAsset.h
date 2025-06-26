#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "KeyItemDataAsset.generated.h"

UENUM(BlueprintType)
enum class EKeyItemType : uint8
{
	Key,
	Tool,
	Ammo,
	Note,
	Weapon
};

USTRUCT(BlueprintType)
struct FKeyItemInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly) FName ID;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) EKeyItemType Type;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) TArray<FName> Dependencies;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) TSubclassOf<AActor> ActorClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawn")
	TArray<FTransform> PossibleSpawns;
};

UCLASS(BlueprintType)
class GRABITELI_API UKeyItemDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FKeyItemInfo> Items;
};
