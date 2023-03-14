// Fill out your copyright notice in the Description page of Project Settings.


#include "SinteractionComponent.h"
#include "SGameplayInterface.h"

// Sets default values for this component's properties
USinteractionComponent::USinteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void USinteractionComponent::PrimaryInteract()
{
	FCollisionObjectQueryParams objectQueryParams;
	objectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	FVector eyeLocation;
	FRotator eyeRotation;

	AActor* myOwner = GetOwner();
	if (myOwner == nullptr)
		return;

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

// Called when the game starts
void USinteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	
}


// Called every frame
void USinteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

