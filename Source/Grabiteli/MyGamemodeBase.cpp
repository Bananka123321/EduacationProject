// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGamemodeBase.h"
#include "GraphicsSettingsManager.h"
#include "MyPlayerController.h"
#include "MainCharacter.h"

AMyGamemodeBase::AMyGamemodeBase()
{
    DefaultPawnClass = AMainCharacter::StaticClass();
    PlayerControllerClass = AMyPlayerController::StaticClass();
}

void AMyGamemodeBase::BeginPlay()
{
    Super::BeginPlay();

    UGraphicsSettingsManager* GraphicsMgr = NewObject<UGraphicsSettingsManager>(this);
    GraphicsMgr->Initialize();
}