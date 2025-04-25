// Fill out your copyright notice in the Description page of Project Settings.


#include "VerdandiViolation.h"

#include "VerdandiItem.h"

UVerdandiViolation::UVerdandiViolation(): Level(EViolationLevel::Warning)
{
	if (IsTemplate())
	{
		Label = FText::FromString(GetClass()->GetName());
	}
}

UVerdandiTimeline* UVerdandiViolation::GetTimeline() const
{
	check(Item);
	return Item->GetTimeline();
}

FText UVerdandiViolation::GetFromText() const
{
	FString Result;
	TArray<UVerdandiItem*> Chain = {Item};
	UVerdandiItem* MaybeParent = Item->GetParent();
	while (MaybeParent)
	{
		Chain.Add(MaybeParent);
		MaybeParent = MaybeParent->GetParent();
	}
	for (int i = Chain.Num() - 1; i >= 0; --i)
	{
		Result += Chain[i]->GetItemName();
		if (i != 0)
		{
			Result += "/";
		}
	}
	return FText::FromString(Result);
}
