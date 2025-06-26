#include "ItemActor.h"
#include "InspectItem.h"
#include "MainCharacter.h"
#include "InventoryComponent.h"
#include "Components/SphereComponent.h"
#include "Components/BillboardComponent.h"
#include "Components/StaticMeshComponent.h"

AItemActor::AItemActor()
{
    PrimaryActorTick.bCanEverTick = false;

    StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
    RootComponent = StaticMesh;

    SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
    SphereCollision->SetupAttachment(StaticMesh);

    InteractIcon = CreateDefaultSubobject<UBillboardComponent>(TEXT("InteractIcon"));
    InteractIcon->SetupAttachment(StaticMesh);
    InteractIcon->SetAbsolute(false, true, false);


    static ConstructorHelpers::FObjectFinder<UTexture2D> DefaultTex(TEXT("Texture2D'/Game/Icons/interact_Icon.interact_Icon'"));
    static ConstructorHelpers::FObjectFinder<UTexture2D> InspectTex(TEXT("Texture2D'/Game/Icons/FloatingCircle.FloatingCircle'"));

    if (InspectTex.Succeeded())
        InspectTexture = InspectTex.Object;

    if (DefaultTex.Succeeded())
        DefaultTexture = DefaultTex.Object;

    SphereCollision->InitSphereRadius(200.0f);
    SphereCollision->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
    SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &AItemActor::OnOverlapBegin);
    SphereCollision->OnComponentEndOverlap.AddDynamic(this, &AItemActor::OnOverlapEnd);

    InteractIcon->bIsScreenSizeScaled = true;
    InteractIcon->SetHiddenInGame(false);
    InteractIcon->SetVisibility(false);

    ItemMesh = nullptr;
    ItemName;
    ItemDescription;
    ItemScale = FVector(1.0f, 1.0f, 1.0f);

    bDebugging = true;
    IconLocation = FVector(0.0f, 0.0f, 45.0f);
    IconScale = FVector(1.0f, 1.0f, 1.0f);
    SphereRadius = 200.0f;

    bInspect = false;
    ItemInspectionRotation = FRotator(0.0f, 0.0f, 0.0f);
    ItemInspectionScale = FVector(0.0f, 0.0f, 0.0f);
}

void AItemActor::SetupIcons()
{
    SphereCollision->SetSphereRadius(SphereRadius);

    InteractIcon->SetRelativeLocation(IconLocation);

    InteractIcon->SetWorldScale3D(IconScale);

    if (bInspect)
        InteractIcon->SetSprite(InspectTexture);
    else
        InteractIcon->SetSprite(DefaultTexture);
}

void AItemActor::SetupMesh()
{
    if (ItemMesh != nullptr) {
        StaticMesh->SetStaticMesh(ItemMesh);
        FTransform NewTransform;
        NewTransform.SetLocation(StaticMesh->GetComponentLocation());
        NewTransform.SetRotation(FQuat(StaticMesh->GetComponentRotation()));
        NewTransform.SetScale3D(ItemScale);
        StaticMesh->SetWorldTransform(NewTransform);
        if (!bInspect) StaticMesh->SetSimulatePhysics(true);
        else StaticMesh->SetSimulatePhysics(false);
    }
}

void AItemActor::Debug(bool Debugging)
{
    SphereCollision->SetVisibility(Debugging);
    InteractIcon->SetVisibility(Debugging);
}

void AItemActor::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);

    SetupIcons();
    SetupMesh();
    Debug(bDebugging);
}

void AItemActor::BeginPlay()
{
    Super::BeginPlay();
}

void AItemActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AItemActor::Interaction_Implementation(AMainCharacter* Character)
{
    if (Character)
    {
        UInventoryComponent* InventoryComp = Character->FindComponentByClass<UInventoryComponent>();

        if (!bInspect && InventoryComp)
        {
            InventoryComp->AddItem(this); 
        }
        else
        {
            if (!InventoryComp)
                return;
            else
            {
                FVector Location = FVector(10000.0f,0.0f,500.0f);
                FRotator Rotation = (ItemInspectionRotation);
                FVector Scale = (ItemInspectionScale);
                
                FActorSpawnParameters SpawnParams;
                SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

                AInspectItem* SpawnedItem = GetWorld()->SpawnActor<AInspectItem>(AInspectItem::StaticClass(), Location, Rotation, SpawnParams);

                if (SpawnedItem)
                {
                    SpawnedItem->SetActorScale3D(ItemInspectionScale);
                    SpawnedItem->SetItemMesh(ItemMesh);
                    SpawnedItem->SetItemScale(ItemScale);

                    if (SpawnedItem->GetClass()->ImplementsInterface(UInteractionInterface::StaticClass()))
                    {
                        IInteractionInterface::Execute_Inspection(SpawnedItem,Character,ItemName,ItemDescription);
                    }
                }
            }
        }
    }
}

void AItemActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
    bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && OtherActor != this)
    {
        InteractIcon->SetVisibility(true);
    }
}

void AItemActor::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (OtherActor && OtherActor != this)
    {
        InteractIcon->SetVisibility(false);
    }
}