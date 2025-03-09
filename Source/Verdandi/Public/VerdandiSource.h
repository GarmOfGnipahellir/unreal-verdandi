// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/Object.h"
#include "VerdandiSource.generated.h"

class UVerdandiTimeline;
class UVerdandiItem;

UCLASS(BlueprintType, Abstract, EditInlineNew, DefaultToInstanced)
class VERDANDI_API UVerdandiSource : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(Category="Verdandi|Source", BlueprintCallable)
	FORCEINLINE TArray<UVerdandiItem*> GetRootItems() { return RootItems; }

	UVerdandiTimeline* GetTimeline();
	void Refresh();
	virtual void FindRootItems(TArray<TObjectPtr<UVerdandiItem>>& OutRootItems) {}

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

private:
	UPROPERTY()
	TObjectPtr<UVerdandiTimeline> Timeline;

	UPROPERTY()
	TArray<TObjectPtr<UVerdandiItem>> RootItems;
};
