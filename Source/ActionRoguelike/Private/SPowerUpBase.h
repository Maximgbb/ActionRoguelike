// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGameplayInterface.h"
#include "GameFramework/Actor.h"
#include "SPowerUpBase.generated.h"

class UStaticMeshComponent;
class USphereComponent;

UCLASS(ABSTRACT)
class ASPowerUpBase : public AActor, public ISGameplayInterface
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USphereComponent* SphereComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* MeshComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float InteractionDistanceSquared;
	
public:	
	ASPowerUpBase();
	
	virtual void Interact_Implementation(class APawn* InstigatorPawn) override;

protected:
	virtual void BeginPlay() override;
};
