// Fill out your copyright notice in the Description page of Project Settings.


#include "SPowerUpBase.h"
#include "Components/SphereComponent.h"

ASPowerUpBase::ASPowerUpBase()
{
	PrimaryActorTick.bCanEverTick = false;

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->SetCollisionObjectType(ECC_WorldDynamic);
	SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SetRootComponent(SphereComp);

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(RootComponent);
}

void ASPowerUpBase::Interact_Implementation(APawn* InstigatorPawn)
{

}

void ASPowerUpBase::BeginPlay()
{
	Super::BeginPlay();
	
}

