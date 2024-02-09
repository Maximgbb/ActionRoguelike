// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/SBTService_CheckAttackRange.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

void USBTService_CheckAttackRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	
	//Check distance between AI pawn and target actor

	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (ensure(BlackboardComp))
	{
		const AActor* TargetActor = Cast<AActor>(BlackboardComp->GetValueAsObject("TargetActor"));
		if(TargetActor)
		{
			const AAIController* MyController = OwnerComp.GetAIOwner();
			if (ensure(MyController))
			{
				const APawn* OwnerPawn = MyController->GetPawn();
				if (ensure(OwnerPawn))
				{
					const float DistanceToTarget = FVector::Distance(TargetActor->GetActorLocation(), OwnerPawn->GetActorLocation());
					const bool bWithinRange = DistanceToTarget < 2000.0f;

					bool bHasLoS = false;
					if (bWithinRange)
					{
						bHasLoS = MyController->LineOfSightTo(TargetActor);
					}

					BlackboardComp->SetValueAsBool(AttackRangeKey.SelectedKeyName, bWithinRange && bHasLoS);
				}
			}
		}
	}
}
