// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/SBTTaskNode_RangedAttack.h"
#include "GameFramework/Character.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type USBTTaskNode_RangedAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const AAIController* OwnerController = OwnerComp.GetAIOwner();
	if (ensure(OwnerController))
	{
		const ACharacter* OwnerCharacter = Cast<ACharacter>(OwnerController->GetPawn());
		if (!OwnerCharacter)
		{
			return EBTNodeResult::Failed;
		}

		const FVector MuzzleLocation = OwnerCharacter->GetMesh()->GetSocketLocation("Muzzle_01");

		const AActor* TargetActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("TargetActor"));
		if (!TargetActor)
		{
			return EBTNodeResult::Failed;
		}

		const FVector Direction = TargetActor->GetActorLocation() - MuzzleLocation;
		const FRotator MuzzleRotation = Direction.Rotation();

		FActorSpawnParameters Params;
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		const AActor* NewProjectile = GetWorld()->SpawnActor<AActor>(ProjectileClass, MuzzleLocation, MuzzleRotation, Params);

		return NewProjectile ? EBTNodeResult::Succeeded : EBTNodeResult::Failed;
	}

	return EBTNodeResult::Failed;
}
