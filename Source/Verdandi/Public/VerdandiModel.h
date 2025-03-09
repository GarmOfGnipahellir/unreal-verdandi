// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class UVerdandiViolation;
struct FVerdandiViolation;

struct FVerdandiItem : TSharedFromThis<FVerdandiItem>
{
	FString Name;
	FString Path;
	FText Label;
	FName Type;

	FQualifiedFrameTime ParentStartTime;
	FQualifiedFrameTime ParentEndTime;

	FQualifiedFrameTime LocalStartTime;
	FQualifiedFrameTime LocalEndTime;

	TSharedPtr<FVerdandiItem> Parent;
	TArray<TSharedPtr<FVerdandiItem>> Children;

	TArray<TSharedPtr<FVerdandiViolation>> Violations;

	void AddViolation(const TSubclassOf<UVerdandiViolation>& Class, const FText& Description);
};

struct FVerdandiViolation : TSharedFromThis<FVerdandiViolation>
{
	TSubclassOf<UVerdandiViolation> Class;

	FText Label;
	FText Description;
};
