#include "KeyItemDistributor.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/World.h"
#include "Algo/Reverse.h"

AKeyItemDistributor::AKeyItemDistributor()
{
    PrimaryActorTick.bCanEverTick = false;
}

void AKeyItemDistributor::BeginPlay()
{
    Super::BeginPlay();

    if (!ItemDataAsset || ItemDataAsset->Items.Num() == 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("KeyItemDistributor: нет данных в ItemDataAsset"));
        return;
    }

    BuildDependencyGraph();
    if (!TopologicalSort())
    {
        UE_LOG(LogTemp, Error, TEXT("KeyItemDistributor: цикл зависимостей!"));
        return;
    }

    DistributeItems();
}



void AKeyItemDistributor::BuildDependencyGraph()
{
    DependencyGraph.Empty();
    for (const FKeyItemInfo& Info : ItemDataAsset->Items)
    {
        DependencyGraph.FindOrAdd(Info.ID);
        for (const FName& Dep : Info.Dependencies)
        {
            DependencyGraph.FindOrAdd(Dep).Add(Info.ID);
        }
    }
}

bool AKeyItemDistributor::TopologicalSort()
{
    TopoSortedIDs.Empty();
    TSet<FName> Temp, Perm;
    for (auto& Pair : DependencyGraph)
    {
        if (!Perm.Contains(Pair.Key))
        {
            if (!DFSVisit(Pair.Key, Temp, Perm))
                return false;
        }
    }
    Algo::Reverse(TopoSortedIDs);
    return true;
}

bool AKeyItemDistributor::DFSVisit(const FName& Node, TSet<FName>& Temp, TSet<FName>& Perm)
{
    if (Temp.Contains(Node)) return false;
    if (Perm.Contains(Node)) return true;

    Temp.Add(Node);
    for (const FName& Next : DependencyGraph[Node])
    {
        if (!DFSVisit(Next, Temp, Perm))
            return false;
    }
    Temp.Remove(Node);
    Perm.Add(Node);
    TopoSortedIDs.Add(Node);
    return true;
}

void AKeyItemDistributor::DistributeItems()
{
    for (const FName& ItemID : TopoSortedIDs)
    {
        const FKeyItemInfo* InfoPtr = nullptr;
        for (const FKeyItemInfo& Info : ItemDataAsset->Items)
        {
            if (Info.ID == ItemID)
            {
                InfoPtr = &Info;
                break;
            }
        }
        if (!InfoPtr || InfoPtr->PossibleSpawns.Num() == 0)
        {
            UE_LOG(LogTemp, Warning, TEXT("No spawn points for %s"), *ItemID.ToString());
            continue;
        }

        int32 Idx = FMath::RandRange(0, InfoPtr->PossibleSpawns.Num() - 1);
        FTransform ChosenTx = InfoPtr->PossibleSpawns[Idx];

        if (InfoPtr->ActorClass)
        {
            FActorSpawnParameters Params;
            AActor* Spawned = GetWorld()->SpawnActor<AActor>(
                InfoPtr->ActorClass,
                ChosenTx,
                Params);

            if (Spawned)
            {
                Assignment.Add(ItemID, Spawned);
            }
        }
    }
}


