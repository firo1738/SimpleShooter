// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"
#include "Blueprint/UserWidget.h"

void AMainPlayerController::BeginPlay() 
{
    Super::BeginPlay();

    HUD = CreateWidget(this, HUDClass);
    if (HUD != nullptr)
    {
        HUD->AddToViewport();
    }     
}

void AMainPlayerController::GameHasEnded(class AActor* EndGameFocus, bool bIsWinner) 
{
    Super::GameHasEnded(EndGameFocus, bIsWinner);

    HUD->RemoveFromViewport();
    
    if(bIsWinner)
    {
        UUserWidget* WinScreen = CreateWidget(this, WinScreenClass);
        if (WinScreen != nullptr)
        {   
            WinScreen->AddToViewport();

            FInputModeUIOnly InputModes;
            InputModes.SetWidgetToFocus(WinScreen->TakeWidget());
            InputModes.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

            SetInputMode(InputModes);

            bShowMouseCursor = true;
        }
        
    }else
    {
        UUserWidget* LoseScreen = CreateWidget(this, LoseScreenClass);
        if (LoseScreen != nullptr)
        {
            LoseScreen->AddToViewport();

            FInputModeUIOnly InputModo;
            InputModo.SetWidgetToFocus(LoseScreen->TakeWidget());
            InputModo.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

            SetInputMode(InputModo);

            bShowMouseCursor = true;
        }
    }
}


