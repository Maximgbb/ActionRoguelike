// Fill out your copyright notice in the Description page of Project Settings.


#include "SAttributeComponent.h"

USAttributeComponent::USAttributeComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	CurrentHealth = MaxHealth;
}

const float USAttributeComponent::GetMaxHealth() const
{
	return MaxHealth;
}

const float USAttributeComponent::GetCurrentHealth() const
{
	return CurrentHealth;
}

bool USAttributeComponent::IsAlive() const
{
	return CurrentHealth > 0.0f;
}

bool USAttributeComponent::IsFullHealth() const
{
	return CurrentHealth < MaxHealth;
}

bool USAttributeComponent::ApplyHealthChange(const float Delta)
{
	const float OldHealth = CurrentHealth;

	CurrentHealth = FMath::Clamp(CurrentHealth + Delta, 0.0f, GetMaxHealth());

	const float ActualDelta = CurrentHealth - OldHealth;
	OnHealthChange.Broadcast(nullptr, this, MaxHealth, CurrentHealth, ActualDelta);

	return ActualDelta != 0.0f;
}
