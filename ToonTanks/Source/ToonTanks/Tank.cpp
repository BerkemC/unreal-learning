// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include <Kismet/GameplayStatics.h>
#include "DrawDebugHelpers.h"

ATank::ATank() : ABasePawn()
{
	PlayerControllerRef = nullptr;

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
	PlayerInputComponent->BindAction(TEXT("Fire"), EInputEvent::IE_Pressed, this, &ATank::Fire);
}

void ATank::BeginPlay()
{
	Super::BeginPlay();

	PlayerControllerRef = Cast<APlayerController>(GetController());
}

void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FHitResult hit;
	if (PlayerControllerRef && 
		PlayerControllerRef->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, hit))
	{
		DrawDebugSphere(GetWorld(), hit.ImpactPoint, 10.0f, 12, FColor::Red);
		RotateTurret(hit.ImpactPoint);
	}
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