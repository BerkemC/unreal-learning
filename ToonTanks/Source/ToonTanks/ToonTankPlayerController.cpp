// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTankPlayerController.h"
#include "GameFramework/Pawn.h"

void AToonTankPlayerController::SetPlayerEnabledState(bool State)
{
	if (State)
	{
		GetPawn()->EnableInput(this);
	}
	else
	{
		GetPawn()->DisableInput(this);
	}

	bShowMouseCursor = State;
}