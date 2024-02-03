// Fill out your copyright notice in the Description page of Project Settings.


#include "SinteractionComponent.h"

#include "SCharacter.h"
#include "SGameplayInterface.h"
#include "Camera/CameraComponent.h"

USinteractionComponent::USinteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void USinteractionComponent::PrimaryInteract()
{
	ASCharacter* OwnerCharacter = Cast<ASCharacter>(GetOwner());
	if (OwnerCharacter == nullptr)
		return;

	const FVector StartLocation = OwnerCharacter->GetCameraComponent()->GetComponentLocation();
	const FVector EndLocation = StartLocation + (OwnerCharacter->GetControlRotation().Vector() * InteractionDistance);

	FCollisionShape Shape;
	Shape.SetSphere(InteractionSphereRadius);
	
	TArray<FHitResult> HitResults;

	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	const bool bBlockingHit = GetWorld()->SweepMultiByObjectType(HitResults, StartLocation, EndLocation, FQuat::Identity, ObjectQueryParams, Shape);

	for (const FHitResult& Hit : HitResults)
	{
		if (AActor* HittedActor = Hit.GetActor())
		{
			if (HittedActor->Implements<USGameplayInterface>())
			{
				APawn* MyPawn = Cast<APawn>(OwnerCharacter);
				ISGameplayInterface::Execute_Interact(HittedActor, MyPawn);
				if (bEnableDebug)
				{
					DrawDebugSphere(GetWorld(), Hit.ImpactPoint, InteractionSphereRadius, 32, (bBlockingHit ? FColor::Green : FColor::Red), false, 2.0f);
				}

				break;
			}
		}
	}

	if (bEnableDebug)
		DrawDebugLine(GetWorld(), StartLocation, EndLocation, (bBlockingHit ? FColor::Green : FColor::Red), false, 2.0f, 0, 2.0f);
}

void USinteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

void USinteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

