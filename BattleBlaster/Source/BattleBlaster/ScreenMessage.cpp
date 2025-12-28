// Fill out your copyright notice in the Description page of Project Settings.


#include "ScreenMessage.h"

void UScreenMessage::SetMessageText(const FString Message) const
{
	MessageTextBlock->SetText(FText::FromString(Message));
}
