#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KeyItemDataAsset.h"
#include "KeyItemDistributor.generated.h"

UCLASS()
class GRABITELI_API AKeyItemDistributor : public AActor
{
	GENERATED_BODY()

public:
	AKeyItemDistributor();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Key Items")
	UKeyItemDataAsset* ItemDataAsset;

	//UPROPERTY(EditAnywhere, Category = "Key Items")
	//TArray<FTransform> SpawnTransforms;

private:
	TMap<FName, TArray<FName>> DependencyGraph;

	TArray<FName> TopoSortedIDs;

	TMap<FName, AActor*> Assignment;

	void BuildDependencyGraph();

	bool TopologicalSort();

	bool DFSVisit(const FName& Node, TSet<FName>& Temp, TSet<FName>& Perm);

	void DistributeItems();
};
