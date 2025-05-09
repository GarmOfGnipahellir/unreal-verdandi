// Fill out your copyright notice in the Description page of Project Settings.


#include "VerdandiItem.h"

#include "VerdandiModule.h"
#include "VerdandiTimeline.h"
#include "VerdandiViolation.h"

FString UVerdandiItem::GetItemDir() const
{
	FString ParentDir = Parent ? Parent->GetItemDir() : GetTimeline()->GetRootDir();
	return FPaths::Combine(ParentDir, GetItemName());
}

FString UVerdandiItem::GetItemPath() const
{
	return FPaths::Combine(GetItemDir(), GetItemName() + "." + GetItemName());
}

void UVerdandiItem::Refresh()
{
	Children.Empty();
	FindChildren(Children);
	for (auto& Child : Children)
	{
		Child->Timeline = GetTimeline();
		Child->Parent = this;
		Child->Refresh();
	}
	FindViolations();
}

void UVerdandiItem::FindViolations()
{
	Violations.Empty();
	for (auto Class : FVerdandiModule::GetViolationTypes())
	{
		UVerdandiViolation* Violation = NewObject<UVerdandiViolation>(this, Class);
		Violation->Item = this;
		if (Violation->TryFix(true)) continue;

		Violations.Add(Violation);
	}
}
