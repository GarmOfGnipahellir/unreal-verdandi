// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VerdandiViolation.h"
#include "VerdandiViolation_MissingSequenceAsset.generated.h"

class UVerdandiItem;
/**
 * 
 */
UCLASS()
class VERDANDI_API UVerdandiViolation_MissingSequenceAsset : public UVerdandiViolation
{
	GENERATED_BODY()

public:
	virtual FText GetLabelText() const override { return FText::FromString("Missing Sequence Asset"); }
	virtual bool TryFix(bool bIsDryRun) override;
};
