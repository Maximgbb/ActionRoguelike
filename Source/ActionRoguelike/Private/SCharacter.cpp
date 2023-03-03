// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ASCharacter::ASCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->bUsePawnControlRotation = true; //This is for rotating the camera from the rotation of our controller.

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComp->SetupAttachment(SpringArmComp);

	GetCharacterMovement()->bOrientRotationToMovement = true; //This will rotate our character (pawn) towards our movement.

	bUseControllerRotationYaw = false;//So our pawn does not rotate when we rotate with the controller.
}

void ASCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASCharacter::MoveForward(float Value)
{
	//This is for our character to rotate and move towards the camera direction while we move forward or backward
	FRotator controlRotator = GetControlRotation();
	controlRotator.Pitch = 0.0f;
	controlRotator.Roll = 0.0f;

	AddMovementInput(controlRotator.Vector(), Value);
}

void ASCharacter::MoveRight(float Value)
{
	//This is to avoid that the character rotates in circles, since when we try to move right or left (we need to use the control rotation right vector)
	FRotator controlRotator = GetControlRotation();
	controlRotator.Pitch = 0.0f;
	controlRotator.Roll = 0.0f;

	FVector RightVector = FRotationMatrix(controlRotator).GetScaledAxis(EAxis::Y);

	AddMovementInput(RightVector, Value);
}

void ASCharacter::PrimaryAttack()
{

	FVector handLocation = GetMesh()->GetSocketLocation("Muzzle_01"); 
	FTransform spawnTM = FTransform(GetControlRotation(), handLocation);
	FActorSpawnParameters spawnParams;
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	GetWorld()->SpawnActor<AActor>(ProjectileClass, spawnTM, spawnParams);
}

void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &ASCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &ASCharacter::AddControllerPitchInput);

	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &ASCharacter::PrimaryAttack);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASCharacter::Jump);
}

