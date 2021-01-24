// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOverGameModeBase.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "SimpleShooter/AI/EnemyAIController.h"

void AGameOverGameModeBase::PawnKilled(APawn* PawnKilled) 
{
    Super::PawnKilled(PawnKilled);

    APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
    
    if (PlayerController != nullptr)
    {
        EndGame(false);
    }

    for (AEnemyAIController* AIController : TActorRange<AEnemyAIController>(GetWorld()))
    {
        if (!AIController->IsDead())
        {
            return;
        }
    }

    EndGame(true);
}

void AGameOverGameModeBase::EndGame(bool bIsPlayerWinner) 
{

   for (AController* Controller : TActorRange<AController>(GetWorld()))
   {
       bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;

       Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
   }
    
}
