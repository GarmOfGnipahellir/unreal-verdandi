// Fill out your copyright notice in the Description page of Project Settings.


#include "VerdandiItem.h"

#include "VerdandiModule.h"
#include "VerdandiViolation.h"

void UVerdandiItem::FindViolations()
{
	for (auto Class : FVerdandiModule::GetViolationTypes())
	{
		UVerdandiViolation* Violation = NewObject<UVerdandiViolation>(this, Class);
		Violation->Item = this;
		if (Violation->TryFix()) continue;

		Violations.Add(Violation);
	}
}
