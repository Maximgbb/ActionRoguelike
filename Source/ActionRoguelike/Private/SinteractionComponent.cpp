// Fill out your copyright notice in the Description page of Project Settings.


#include "SinteractionComponent.h"
#include "SGameplayInterface.h"

USinteractionComponent::USinteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void USinteractionComponent::PrimaryInteract()
{
	FCollisionObjectQueryParams objectQueryParams;
	objectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	AActor* myOwner = GetOwner();
	if (myOwner == nullptr)
		return;

	FVector eyeLocation;
	FRotator eyeRotation;

	myOwner->GetActorEyesViewPoint(eyeLocation, eyeRotation);
	FVector endLocation = eyeLocation + (eyeRotation.Vector() * InteractionDistance);

	TArray<FHitResult> hitResults;

	FCollisionShape shape;
	shape.SetSphere(InteractionSphereRadius);

	bool bBlockingHit = GetWorld()->SweepMultiByObjectType(hitResults, eyeLocation, endLocation, FQuat::Identity, objectQueryParams, shape);

	FColor linearColor = bBlockingHit ? FColor::Green : FColor::Red;

	for (FHitResult hit : hitResults)
	{
		AActor* hittedActor = hit.GetActor();
		if (hittedActor != nullptr)
		{
			if (hittedActor->Implements<USGameplayInterface>())
			{
				APawn* myPawn = Cast<APawn>(myOwner);
				ISGameplayInterface::Execute_Interact(hittedActor, myPawn);
				if (bEnableDebug)
				{
					DrawDebugSphere(GetWorld(), hit.ImpactPoint, InteractionSphereRadius, 32, linearColor, false, 2.0f);
				}

				break;
			}
		}
	}

	if (bEnableDebug)
		DrawDebugLine(GetWorld(), eyeLocation, endLocation, linearColor, false, 2.0f, 0, 2.0f);
}

void USinteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

void USinteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

