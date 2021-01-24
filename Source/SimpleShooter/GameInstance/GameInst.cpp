// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInst.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"


UGameInst::UGameInst(const FObjectInitializer & ObjectInializer) 
{
    ConstructorHelpers::FClassFinder<UUserWidget> MenuBPClass(TEXT("/Game/Blurprints/Widgets/Menus/WBP_MainMenu"));
    ConstructorHelpers::FClassFinder<UUserWidget> CharSelBPClass(TEXT("/Game/Blurprints/Widgets/Menus/WBP_CharacterSel"));

    MenuClass = MenuBPClass.Class;
    CharSelClass = CharSelBPClass.Class;
}

void UGameInst::Init() 
{
    //logs here
}

void UGameInst::LoadMenu() 
{
    UUserWidget* Main = CreateWidget<UUserWidget>(this, MenuClass);

    Main->AddToViewport();

    APlayerController* PlayerCont = GetFirstLocalPlayerController();

    FInputModeUIOnly InputModo;
    InputModo.SetWidgetToFocus(Main->TakeWidget());
    InputModo.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

    PlayerCont->SetInputMode(InputModo);

    PlayerCont->bShowMouseCursor = true;
}

void UGameInst::CharacterSelect() 
{
    UUserWidget* CharS = CreateWidget<UUserWidget>(this, CharSelClass);

    CharS->AddToViewport();

    APlayerController* PlayerCont1 = GetFirstLocalPlayerController();

    FInputModeUIOnly InputModes;
    InputModes.SetWidgetToFocus(CharS->TakeWidget());
    InputModes.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

    PlayerCont1->SetInputMode(InputModes);

    PlayerCont1->bShowMouseCursor = true;
}

