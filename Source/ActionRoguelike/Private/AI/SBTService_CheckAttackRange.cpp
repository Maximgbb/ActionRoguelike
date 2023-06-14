// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBTService_CheckAttackRange.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

void USBTService_CheckAttackRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	
	//Check distance between AI pawn and target actor

	UBlackboardComponent* blackboardComp = OwnerComp.GetBlackboardComponent();
	if (ensure(blackboardComp))
	{
		AActor* targetActor = Cast<AActor>(blackboardComp->GetValueAsObject("TargetActor"));
		if(targetActor)
		{
			AAIController* myController = OwnerComp.GetAIOwner();
			if (ensure(myController))
			{
				APawn* ownerPawn = myController->GetPawn();
				if (ensure(ownerPawn))
				{
					float distanceToTarget = FVector::Distance(targetActor->GetActorLocation(), ownerPawn->GetActorLocation());
					bool bWithinRange = distanceToTarget < 2000.0f;

					bool bHasLOS = false;
					if (bWithinRange)
					{
						bHasLOS = myController->LineOfSightTo(targetActor);
					}

					blackboardComp->SetValueAsBool(AttackRangeKey.SelectedKeyName, bWithinRange && bHasLOS);
				}
			}
		}
	}
}
