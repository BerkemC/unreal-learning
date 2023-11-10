// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include <Kismet/GameplayStatics.h>

ATank::ATank() : ABasePawn()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
}

void ATank::Move(float Value)
{
	FVector deltaLocation(Value * MovementSpeed * UGameplayStatics::GetWorldDeltaSeconds(this), 0, 0);
	AddActorLocalOffset(deltaLocation, true);
}

void ATank::Turn(float Value)
{
	FRotator deltaRotation(0, Value * TurnSpeed * UGameplayStatics::GetWorldDeltaSeconds(this), 0);
	AddActorLocalRotation(deltaRotation, true);
}
