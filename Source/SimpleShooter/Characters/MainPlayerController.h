// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"

class UUserWidget;
UCLASS()
class SIMPLESHOOTER_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void GameHasEnded(class AActor* EndGameFocus = nullptr, bool bIsWinner = false) override;	

protected:
	virtual void BeginPlay() override;
private:

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget>LoseScreenClass;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget>WinScreenClass;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget>HUDClass;
	UPROPERTY(EditAnywhere)
	UUserWidget* HUD;	
};
