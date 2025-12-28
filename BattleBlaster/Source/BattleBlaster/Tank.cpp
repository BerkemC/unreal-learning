// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

ATank::ATank() : ABasePawn()
{
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));

	SpringArmComponent->SetupAttachment(RootComponent);
	CameraComponent->SetupAttachment(SpringArmComponent);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = Cast<APlayerController>(Controller);
	if(PlayerController)
	{
		if(const ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer())
		{
			if(UEnhancedInputLocalPlayerSubsystem* Subsystem
				= ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer))
			{
				Subsystem->AddMappingContext(DefaultMappingContext, 0);
			}
		}
	}

	SetPlayerEnabled(false);
}

// Called every frame
void ATank::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(PlayerController)
	{
		FHitResult LineTraceHit;
		PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, LineTraceHit);
		RotateTurret(LineTraceHit.ImpactPoint);
	}
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if(UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATank::MoveInput);
		EnhancedInputComponent->BindAction(RotateAction, ETriggerEvent::Triggered, this, &ATank::RotateInput);
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Started, this, &ATank::Fire);
	}
}

void ATank::HandleDestruction()
{
	Super::HandleDestruction();

	IsAlive = false;
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
	SetPlayerEnabled(false);
}

void ATank::SetPlayerEnabled(const bool Enabled)
{
	if(!PlayerController)
	{
		return;
	}

	if(Enabled)
	{
		EnableInput(PlayerController);
	}
	else
	{
		DisableInput(PlayerController);
		PlayerController->bShowMouseCursor = false;
	}
}

bool ATank::IsDead() const
{
	return !IsAlive;
}

void ATank::MoveInput(const FInputActionValue& InputValue)
{
	const float Value = InputValue.Get<float>();
	AddActorLocalOffset(
	FVector::XAxisVector * Value * MovementSpeed * GetWorld()->DeltaTimeSeconds, true);
}

void ATank::RotateInput(const FInputActionValue& InputValue)
{
	const float Value = InputValue.Get<float>();
	const FVector DeltaRotationVector = FVector::YAxisVector * Value * RotationSpeed * GetWorld()->DeltaTimeSeconds;
	AddActorLocalRotation(
		FRotator(DeltaRotationVector.X, DeltaRotationVector.Y, DeltaRotationVector.Z),
		true);
}