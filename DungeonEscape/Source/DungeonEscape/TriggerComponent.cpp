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
    if((++OverlappingActorCount) > 1)
    {
        return;
    }
    
    SetMoverStateForPressurePlate(true, OtherActor);
}

void UTriggerComponent::OnOverlapEnd(
        UPrimitiveComponent* OverlappedComp,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex)
{
    if((--OverlappingActorCount) != 0)
    {
        return;
    }
    
    SetMoverStateForPressurePlate(false, OtherActor);
}

void UTriggerComponent::SetMoverStateForPressurePlate(const bool TargetState, const AActor* OtherActor)
{
    if(!OtherActor || !OtherActor->ActorHasTag(RequiredPressurePlateTag))
    {
        return;
    }
    
    SetTrigger(TargetState);
}

void UTriggerComponent::SetTrigger(const bool State)
{
    if(!MoverComponent)
    {
        return;
    }

    MoverComponent->SetShouldMove(State);
}


