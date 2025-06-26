#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractionInterface.h"
#include "ItemActor.generated.h"

UCLASS()
class GRABITELI_API AItemActor : public AActor, public IInteractionInterface
{
	GENERATED_BODY()

public:
	AItemActor();
	virtual void OnConstruction(const FTransform& Transform) override;
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void Interaction_Implementation(AMainCharacter* Character) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USphereComponent* SphereCollision;

	UPROPERTY(VisibleAnywhere)
	class UBillboardComponent* InteractIcon;

protected:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Public | Mesh")
	UStaticMesh* ItemMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Public | Mesh")
	FText ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Public | Mesh")
	FText ItemDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Public | Mesh")
	FVector ItemScale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Public | Interaction | Settings")
	bool bDebugging;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Public | Interaction | Settings")
	FVector IconLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Public | Interaction | Settings")
	FVector IconScale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Public | Interaction | Settings")
	float SphereRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Public | Interaction | Inspection")
	bool bInspect = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Public | Interaction | Inspection")
	FRotator ItemInspectionRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Public | Interaction | Inspection")
	FVector ItemInspectionScale;

	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	class UTexture2D* InspectTexture;

	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	class UTexture2D* DefaultTexture;

	void SetupMesh();
	void Debug(bool Debug);

public:
	
	UStaticMesh* GetItemMesh() const { return ItemMesh; }
	FVector GetItemScale() const { return ItemScale; }
	FText GetItemName() const { return ItemName; }
	FText GetItemDescription() const { return ItemDescription; }
	FVector GetIconLocation() const { return IconLocation; }
	FVector GetIconScale() const { return IconScale; }
	float GetSphereRadius() const { return SphereRadius; }
	bool GetbInspect() const { return bInspect; }

	void SetupIcons();
	
	void SetItemMesh(UStaticMesh* NewMesh) { ItemMesh = NewMesh; StaticMesh->SetStaticMesh(ItemMesh); }
	void SetItemScale(FVector NewItemScale) { ItemScale = NewItemScale; StaticMesh->SetWorldScale3D(ItemScale); }
	void SetItemName(const FText& NewName) { ItemName = NewName; }
	void SetItemDescription(const FText& NewDescription) { ItemDescription = NewDescription; }
	void SetIconLocation(const FVector& NewLocation) { IconLocation = NewLocation; }
	void SetIconScale(const FVector& NewScale) { IconScale = NewScale; }
	void SetSphereRadius(float NewRadius) { SphereRadius = NewRadius; }
	void SetbInspect(bool bNewInspect) { bInspect = bNewInspect; }
};
