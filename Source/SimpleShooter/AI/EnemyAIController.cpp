// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "SimpleShooter/Characters/MainCharacter.h"

void AEnemyAIController::BeginPlay() 
{
    Super::BeginPlay();

    if(AIBehavior != nullptr)
    {
        RunBehaviorTree(AIBehavior); 
        GetBlackboardComponent()->SetValueAsVector(TEXT("PawnLocation"), GetPawn()->GetActorLocation());
        GetBlackboardComponent()->SetValueAsRotator(TEXT("PawnRotation"), GetPawn()->GetControlRotation());
    }    
}

void AEnemyAIController::Tick(float DeltaTime) 
{
    Super::Tick(DeltaTime);
}

bool AEnemyAIController::IsDead() const
{
    AMainCharacter* ControllerCharacter = Cast<AMainCharacter>(GetPawn());

    if (ControllerCharacter != nullptr)
    {
        return ControllerCharacter->IsDead();
    }

    return true;
}
