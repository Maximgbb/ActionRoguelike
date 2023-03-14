// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SGameplayInterface.h"
#include "SItemChest.generated.h"

UCLASS()
class ACTIONROGUELIKE_API ASItemChest : public AActor, public ISGameplayInterface
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	float TargetPitch = 0.0f;

protected:

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* LidMesh;
	
public:	
	// Sets default values for this actor's properties
	ASItemChest();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Interact_Implementation(class APawn* InstigatorPawn) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
