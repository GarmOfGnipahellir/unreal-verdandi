// Fill out your copyright notice in the Description page of Project Settings.


#include "VerdandiModel.h"

#include "VerdandiViolation.h"


void FVerdandiItem::AddViolation(const TSubclassOf<UVerdandiViolation>& Class, const FText& Description)
{
	TSharedPtr<FVerdandiViolation> NewViolation = MakeShared<FVerdandiViolation>();
	NewViolation->Class = Class;
	NewViolation->Description = Description;
	NewViolation->Label = Class.GetDefaultObject()->GetLabelText();
	Violations.Add(NewViolation);
}
