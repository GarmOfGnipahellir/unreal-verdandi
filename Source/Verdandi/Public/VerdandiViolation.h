// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "VerdandiViolation.generated.h"

class UVerdandiTimeline;
class UVerdandiItem;
/**
 * 
 */
UCLASS(Abstract)
class VERDANDI_API UVerdandiViolation : public UObject
{
	GENERATED_BODY()

public:
	TObjectPtr<UVerdandiItem> Item;
	FText Description;

	virtual FText GetLabelText() const;
	virtual FText GetDescription() const { return Description; }

	virtual bool TryFix(bool bIsDryRun = false) PURE_VIRTUAL(UVerdandiViolation, return true;)

	UVerdandiTimeline* GetTimeline() const;
	FText GetFromText() const;
};
