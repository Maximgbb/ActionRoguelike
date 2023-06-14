// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

void ASAIController::BeginPlay()
{
	Super::BeginPlay();
	
	RunBehaviorTree(BehaviourTree);

	APawn* playerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	if (playerPawn)
	{
		GetBlackboardComponent()->SetValueAsObject("TargetActor", playerPawn);
	}
}
