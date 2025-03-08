// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "VerdandiItem.generated.h"

class UVerdandiViolation;
/**
 * 
 */
UCLASS(BlueprintType, Abstract)
class VERDANDI_API UVerdandiItem : public UObject
{
	GENERATED_BODY()

public:
	TArray<TObjectPtr<UVerdandiViolation>> Violations;
	
	UFUNCTION(Category="Verdandi|Item", BlueprintCallable)
	virtual FText GetLabelText() const PURE_VIRTUAL(UVerdandiItem::GetLabelText, return FText::FromString("No name"););

	UFUNCTION(Category="Verdandi|Item", BlueprintCallable)
	virtual FQualifiedFrameTime GetParentStartTime() const
	{
		return FQualifiedFrameTime(FFrameNumber(0), FFrameRate(30, 1));
	}

	UFUNCTION(Category="Verdandi|Item", BlueprintCallable)
	virtual FQualifiedFrameTime GetParentEndTime() const
	{
		return FQualifiedFrameTime(FFrameNumber(0), FFrameRate(30, 1));
	}

	UFUNCTION(Category="Verdandi|Item", BlueprintCallable)
	virtual FQualifiedFrameTime GetLocalStartTime() const
	{
		return FQualifiedFrameTime(FFrameNumber(0), FFrameRate(30, 1));
	}

	UFUNCTION(Category="Verdandi|Item", BlueprintCallable)
	virtual FQualifiedFrameTime GetLocalEndTime() const
	{
		return FQualifiedFrameTime(FFrameNumber(0), FFrameRate(30, 1));
	}

	UFUNCTION(Category="Verdandi|Item", BlueprintCallable)
	virtual TArray<UVerdandiItem*> GetChildren() { return TArray<UVerdandiItem*>(); }

	void FindViolations();
};
