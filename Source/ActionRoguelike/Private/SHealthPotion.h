// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SPowerUpBase.h"
#include "SHealthPotion.generated.h"

/**
 * 
 */
UCLASS()
class ASHealthPotion : public ASPowerUpBase
{
	GENERATED_BODY()

public:

	virtual void Interact_Implementation(class APawn* InstigatorPawn) override;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float HealingAmount;
};
