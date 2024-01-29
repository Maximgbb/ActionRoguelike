// Fill out your copyright notice in the Description page of Project Settings.


#include "SinteractionComponent.h"
#include "SGameplayInterface.h"

USinteractionComponent::USinteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void USinteractionComponent::PrimaryInteract()
{
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	AActor* MyOwner = GetOwner();
	if (MyOwner == nullptr)
		return;

	FVector EyeLocation;
	FRotator EyeRotation;

	MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);
	FVector EndLocation = EyeLocation + (EyeRotation.Vector() * InteractionDistance);

	FCollisionShape Shape;
	Shape.SetSphere(InteractionSphereRadius);
	
	TArray<FHitResult> HitResults;

	bool bBlockingHit = GetWorld()->SweepMultiByObjectType(HitResults, EyeLocation, EndLocation, FQuat::Identity, ObjectQueryParams, Shape);

	for (const FHitResult& Hit : HitResults)
	{
		AActor* HittedActor = Hit.GetActor();
		if (HittedActor != nullptr)
		{
			if (HittedActor->Implements<USGameplayInterface>())
			{
				APawn* MyPawn = Cast<APawn>(MyOwner);
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
		DrawDebugLine(GetWorld(), EyeLocation, EndLocation, (bBlockingHit ? FColor::Green : FColor::Red), false, 2.0f, 0, 2.0f);
}

void USinteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

void USinteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

