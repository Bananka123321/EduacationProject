#include "InspectItem.h"
#include "InspectWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/TextureRenderTarget2D.h"
#include "MainCharacter.h"
#include "MyPlayerController.h"
#include "UObject/ConstructorHelpers.h"

AInspectItem::AInspectItem()
{
    PrimaryActorTick.bCanEverTick = false;

    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

    StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
    StaticMesh->SetupAttachment(RootComponent);

    CaptureComponent = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("CaptureComponent"));
    CaptureComponent->SetupAttachment(RootComponent);
    CaptureComponent->SetRelativeLocation(FVector(-280.0f, 0.0f, 33.0f));
    
    static ConstructorHelpers::FObjectFinder<UTextureRenderTarget2D> FoundRenderTarget(TEXT("/Game/Framework/RT_Inspect.RT_Inspect"));

    if (FoundRenderTarget.Succeeded())
    {
        PreconfiguredRenderTarget = FoundRenderTarget.Object;
        CaptureComponent->TextureTarget = PreconfiguredRenderTarget;
    }
    CaptureComponent->bCaptureEveryFrame = true;
    CaptureComponent->bCaptureOnMovement = false;
    CaptureComponent->FOVAngle = 50.0f;
    CaptureComponent->ShowFlags.SetAtmosphere(false);
    ItemMesh = nullptr;
    ItemScale = FVector(1.0f, 1.0f, 1.0f);

    static ConstructorHelpers::FClassFinder<UInspectWidget> WidgetFinder(TEXT("/Game/Framework/Widgets/WB_Inspect.WB_Inspect_C"));  
    if (WidgetFinder.Succeeded())
    {
        InspectWidgetClass = WidgetFinder.Class;
    }
}

void AInspectItem::BeginPlay()
{
    Super::BeginPlay();

    EnableInput(GetWorld()->GetFirstPlayerController());
    PC = Cast<AMyPlayerController>(GetWorld()->GetFirstPlayerController());

    if (InputComponent)
    {
        InputComponent->BindKey(EKeys::LeftMouseButton, IE_Pressed, this, &AInspectItem::OnLeftMousePressed);
        InputComponent->BindKey(EKeys::LeftMouseButton, IE_Released, this, &AInspectItem::OnLeftMouseReleased);
        InputComponent->BindKey(EKeys::RightMouseButton, IE_Released, this, &AInspectItem::ResetRotation);
        InputComponent->BindKey(EKeys::Q, IE_Pressed, this, &AInspectItem::Exit);
        InputComponent->BindAxis("Zoom", this, &AInspectItem::ZoomItem);
    }
}

void AInspectItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInspectItem::OnLeftMousePressed() {
    bRotate = true;
    PC->bShowMouseCursor = false;
}

void AInspectItem::OnLeftMouseReleased(){
    bRotate = false;
    PC->bShowMouseCursor = true;
}

void AInspectItem::ResetRotation(){
    StaticMesh->SetWorldRotation(FRotator(0.0f, 0.0f, 0.0f));
    CaptureComponent->FOVAngle = 50.0f;
}

void AInspectItem::RotateItemX(float Value)
{
    if (bRotate && StaticMesh)
    {
        FRotator RotationDelta(0.0f, Value * -3.0f, 0.0f);
        StaticMesh->AddLocalRotation(RotationDelta);
    }
}

void AInspectItem::RotateItemY(float Value)
{
    if (bRotate && StaticMesh)
    {
        FRotator RotationDelta(Value * -3.0f, 0.0f, 0.0f);
        StaticMesh->AddLocalRotation(RotationDelta);
    }
}


void AInspectItem::ZoomItem(float Value)
{
    if (FMath::Abs(Value) > KINDA_SMALL_NUMBER)
    {
        CaptureComponent->FOVAngle = FMath::Clamp(CaptureComponent->FOVAngle - (Value * 5.0f), 30.0f, 80.0f);
    }
}


void AInspectItem::Exit()
{
    if (!PC || !MyCharacter) return;

    PC->SetIgnoreMoveInput(false);
    PC->SetIgnoreLookInput(false);

    if (PC->InputComponent)
    {
        for (int32 i = PC->InputComponent->AxisBindings.Num() - 1; i >= 0; --i)
        {
            FInputAxisBinding& Binding = PC->InputComponent->AxisBindings[i];
            if (Binding.AxisName == "Turn" || Binding.AxisName == "LookUp")
            {
                PC->InputComponent->AxisBindings.RemoveAt(i);
            }
        }

        PC->InputComponent->BindAxis("Turn", MyCharacter, &AMainCharacter::AddControllerYawInput);
        PC->InputComponent->BindAxis("LookUp", MyCharacter, &AMainCharacter::AddControllerPitchInput);
    }

    PC->bShowMouseCursor = false;
    PC->SetInputMode(FInputModeGameOnly());
    PC->bIsInspecting = false;
    if (InspectWidgetInstance)
    {
        InspectWidgetInstance->RemoveFromParent();
    }

    this->Destroy();
}

void AInspectItem::Inspection_Implementation(AMainCharacter* Character, const FText& ItemName, const FText& ItemDescription)
{
    MyCharacter = Character;
    PC = Cast<AMyPlayerController>(MyCharacter->GetController());
    if (!PC) return;

    PC->SetIgnoreMoveInput(true);
    PC->SetIgnoreLookInput(true);

    PC->bShowMouseCursor = true;
    PC->SetInputMode(FInputModeGameAndUI());
    PC->bIsInspecting = true;

    PC->InputComponent->BindAxis("Turn", this, &AInspectItem::RotateItemX);
    PC->InputComponent->BindAxis("LookUp", this, &AInspectItem::RotateItemY);
    PC->InputComponent->BindAxis("MouseWheelAxis", this, &AInspectItem::ZoomItem);

    if (InspectWidgetClass)
    {
        InspectWidgetInstance = CreateWidget<UInspectWidget>(GetWorld(), InspectWidgetClass);
        if (InspectWidgetInstance)
        {
            InspectWidgetInstance->InitializeWidget(ItemName, ItemDescription);
            InspectWidgetInstance->AddToViewport();
        }
    }
}
