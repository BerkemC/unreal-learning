// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDWidget.h"

#include "Components/ProgressBar.h"

void UHUDWidget::SetHealthBarPercent(float NewValue)
{
	if(!HealthBar)
	{
		return;
	}

	HealthBar->SetPercent(FMath::Clamp(NewValue, 0, 1.0f));
}
