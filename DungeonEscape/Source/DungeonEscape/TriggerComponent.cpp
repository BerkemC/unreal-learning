// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"

#include "MoverComponent.h"

UTriggerComponent::UTriggerComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UTriggerComponent::BeginPlay()
{
    Super::BeginPlay();

    if(MoverActor)
    {
        MoverComponent = MoverActor->FindComponentByClass<UMoverComponent>();
    }

    if(IsPressurePlate)
    {
        OnComponentBeginOverlap.AddDynamic(this, &UTriggerComponent::OnOverlapBegin);
        OnComponentEndOverlap.AddDynamic(this, &UTriggerComponent::OnOverlapEnd);    
    }
}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UTriggerComponent::OnOverlapBegin(
        UPrimitiveComponent* OverlappedComp,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex,
        bool bFromSweep,
        const FHitResult& SweepResult)
{
    if(!OtherActor->ActorHasTag(RequiredPressurePlateTag))
    {
        return;
    }
    
    SetMoverState(true);
}

void UTriggerComponent::OnOverlapEnd(
        UPrimitiveComponent* OverlappedComp,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex)
{
    if(!OtherActor->ActorHasTag(RequiredPressurePlateTag))
    {
        return;
    }
    
    SetMoverState(false);
}

void UTriggerComponent::SetMoverState(const bool State)
{
    if(!MoverComponent)
    {
        return;
    }

    MoverComponent->SetShouldMove(State);
}


