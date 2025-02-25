// Fill out your copyright notice in the Description page of Project Settings.


#include "VerdandiTimelineFactory.h"

#include "VerdandiTimeline.h"

UVerdandiTimelineFactory::UVerdandiTimelineFactory(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SupportedClass = UVerdandiTimeline::StaticClass();
	bCreateNew = true;
	bEditAfterNew = true;
}

UObject* UVerdandiTimelineFactory::FactoryCreateNew(
	UClass* InClass,
	UObject* InParent,
	FName InName,
	EObjectFlags Flags,
	UObject* Context,
	FFeedbackContext* Warn
)
{
	return NewObject<UVerdandiTimeline>(InParent, InClass, InName, Flags);
}

bool UVerdandiTimelineFactory::ShouldShowInNewMenu() const
{
	return true;
}
