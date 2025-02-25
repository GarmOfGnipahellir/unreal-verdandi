// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/Object.h"
#include "VerdandiSource.generated.h"

class UVerdandiItem;

/**
 * 
 */
UCLASS(BlueprintType, Abstract, EditInlineNew, DefaultToInstanced)
class VERDANDI_API UVerdandiSource : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(Category="Verdandi|Source", BlueprintCallable)
	virtual TArray<UVerdandiItem*> GetRootItems() { return TArray<UVerdandiItem*>(); }
};
