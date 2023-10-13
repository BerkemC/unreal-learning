// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	World = GetWorld();
	Handle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!IsGrabbing)
	{
		if (GrabbedActor)
		{
			DropGrabbedActor();
		}
		return;
	}

	if (GrabbedActor)
	{
		MoveGrabbedActor();
	}
	else
	{
		TryGrabActor();
	}
}

void UGrabber::TryGrabActor()
{
	FVector location = GetComponentLocation();
	FVector forward = GetForwardVector();

	FVector end = location + forward * MaxGrabDistance;

	DrawDebugLine(
		World,
		location,
		end,
		FColor::Red);

	FCollisionShape collisionShape = FCollisionShape::MakeSphere(GrabRadius);
	FHitResult hit;
	if (World->SweepSingleByChannel(
		hit,
		location,
		end,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		collisionShape))
	{
		GrabActor(hit);
	}
}

void UGrabber::SetGrabbing(bool value)
{
	if (IsGrabbing == value)
	{
		return;
	}

	if (!value)
	{
		DropGrabbedActor();
	}

	IsGrabbing = value;
	GrabbedActor = nullptr;
}

void UGrabber::GrabActor(const FHitResult& hitResult)
{
	if (GrabbedActor)
	{
		return;
	}

	GrabbedActor = hitResult.GetActor();

	if (!GrabbedActor)
	{
		return;
	}

	GrabbedActor = hitResult.GetActor();

	if (!Handle)
	{
		return;
	}

	UPrimitiveComponent* component = hitResult.GetComponent();
	component->WakeAllRigidBodies();
	Handle->GrabComponentAtLocationWithRotation(
		component,
		NAME_None,
		hitResult.ImpactPoint,
		GetComponentRotation());
}

void UGrabber::DropGrabbedActor()
{
	GrabbedActor = nullptr;

	if (!Handle)
	{
		return;
	}

	UPrimitiveComponent* component = Handle->GetGrabbedComponent();
	
	if (!component)
	{
		return;
	}

	component->WakeAllRigidBodies();
	Handle->ReleaseComponent();
}

void UGrabber::MoveGrabbedActor()
{
	FVector location = GetComponentLocation();
	FVector forward = GetForwardVector();

	FVector end = location + forward * HoldDistance;

	if (!Handle)
	{
		return;
	}

	Handle->SetTargetLocationAndRotation(end, GetComponentRotation());
}