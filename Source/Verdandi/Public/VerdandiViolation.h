// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "VerdandiViolation.generated.h"

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

	virtual FText GetLabelText() const;

	virtual bool TryFix() const PURE_VIRTUAL(UVerdandiViolation, return true;)

	FORCEINLINE bool IsDryRun() const { return bIsDryRun; }

private:
	bool bIsDryRun;
};
