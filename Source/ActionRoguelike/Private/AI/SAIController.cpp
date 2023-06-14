// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

void ASAIController::BeginPlay()
{
	Super::BeginPlay();
	
	if (ensureMsgf(BehaviourTree, TEXT("Behaviour tree is nullptr! Please assign BehaviourTree value in your AI controller.")))
	{
		RunBehaviorTree(BehaviourTree);
	}

	//This is being done with a pawn sensing component inside the AI character
// 	APawn* playerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
// 	if (playerPawn)
// 	{
// 		GetBlackboardComponent()->SetValueAsObject("TargetActor", playerPawn);
// 	}
}
