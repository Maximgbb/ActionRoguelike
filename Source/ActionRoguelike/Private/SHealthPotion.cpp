// Fill out your copyright notice in the Description page of Project Settings.


#include "SHealthPotion.h"
#include "SAttributeComponent.h"
#include "Components/SphereComponent.h"

void ASHealthPotion::Interact_Implementation(APawn* InstigatorPawn)
{
	Super::Interact_Implementation(InstigatorPawn);

	USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(InstigatorPawn->GetComponentByClass(USAttributeComponent::StaticClass()));
	if (AttributeComp && AttributeComp->GetCurrentHealth() < AttributeComp->GetMaxHealth())
	{
		AttributeComp->ApplyHealthChange(HealingAmount);

		SphereComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		MeshComp->SetVisibility(false);
		GetWorldTimerManager().SetTimer(HealingTimerHandle, this, &ASHealthPotion::StartCooldown, Cooldown,false);
	}
}

void ASHealthPotion::StartCooldown() const
{
	MeshComp->SetVisibility(true);
	SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}
