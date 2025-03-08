// Fill out your copyright notice in the Description page of Project Settings.


#include "VerdandiViolation.h"

FText UVerdandiViolation::GetLabelText() const
{
	return FText::FromString(GetClass()->GetName());
}
