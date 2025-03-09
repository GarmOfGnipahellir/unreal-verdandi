// Fill out your copyright notice in the Description page of Project Settings.


#include "VerdandiViolation.h"

#include "VerdandiItem.h"

FText UVerdandiViolation::GetLabelText() const
{
	return FText::FromString(GetClass()->GetName());
}

UVerdandiTimeline* UVerdandiViolation::GetTimeline() const
{
	check(Item);
	return Item->GetTimeline();
}
