// Fill out your copyright notice in the Description page of Project Settings.


#include "VerdandiSource.h"

#include "VerdandiItem.h"
#include "VerdandiTimeline.h"


UVerdandiTimeline* UVerdandiSource::GetTimeline()
{
	if (!Timeline)
	{
		Timeline = Cast<UVerdandiTimeline>(GetOuter());
	}
	check(Timeline);
	return Timeline;
}

void UVerdandiSource::Refresh()
{
	RootItems.Empty();
	FindRootItems(RootItems);

	for (auto& Item : RootItems)
	{
		Item->Timeline = GetTimeline();
		Item->Refresh();
	}
}

void UVerdandiSource::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	UObject::PostEditChangeProperty(PropertyChangedEvent);
}
