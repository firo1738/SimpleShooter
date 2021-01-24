// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_Shoot.h"
#include "AIController.h"
#include "SimpleShooter/GameOverGameModeBase.h"
#include "SimpleShooter/Characters/MainCharacter.h"


UBTTaskNode_Shoot::UBTTaskNode_Shoot() 
{
    NodeName = TEXT("Shoot");
}

EBTNodeResult::Type UBTTaskNode_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) 
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    if (OwnerComp.GetAIOwner() == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    AMainCharacter* Shooting = Cast<AMainCharacter>(OwnerComp.GetAIOwner()->GetPawn());

    if (Shooting == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    Shooting->Shoot();

    return EBTNodeResult::Succeeded;    
}
