// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameInst.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API UGameInst : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UGameInst(const FObjectInitializer & ObjectInializer);

	virtual void Init();

	UFUNCTION(BlueprintCallable)
	void LoadMenu();
	UFUNCTION(BlueprintCallable)
	void CharacterSelect();

private:
	TSubclassOf<class UUserWidget> MenuClass;	
	TSubclassOf<class UUserWidget> CharSelClass;
};
