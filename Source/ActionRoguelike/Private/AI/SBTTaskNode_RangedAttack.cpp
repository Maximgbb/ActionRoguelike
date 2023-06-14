// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBTTaskNode_RangedAttack.h"
#include "GameFramework/Character.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type USBTTaskNode_RangedAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* ownerController = OwnerComp.GetAIOwner();
	if (ensure(ownerController))
	{
		ACharacter* ownerCharacter = Cast<ACharacter>(ownerController->GetPawn());
		if (!ownerCharacter)
		{
			return EBTNodeResult::Failed;
		}

		FVector muzzleLocation = ownerCharacter->GetMesh()->GetSocketLocation("Muzzle_01");

		AActor* targetActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("TargetActor"));
		if (!targetActor)
		{
			return EBTNodeResult::Failed;
		}

		FVector direction = targetActor->GetActorLocation() - muzzleLocation;
		FRotator muzzleRotation = direction.Rotation();

		FActorSpawnParameters params;
		params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		AActor* newProjectile = GetWorld()->SpawnActor<AActor>(ProjectileClass, muzzleLocation, muzzleRotation, params);

		return newProjectile ? EBTNodeResult::Succeeded : EBTNodeResult::Failed;
	}

	return EBTNodeResult::Failed;
}
