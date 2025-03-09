// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "VerdandiItem.generated.h"

class UVerdandiSource;
class UVerdandiTimeline;
class UVerdandiViolation;

UCLASS(BlueprintType, Abstract, Transient)
class VERDANDI_API UVerdandiItem : public UObject
{
	GENERATED_BODY()

public:
	TArray<TObjectPtr<UVerdandiViolation>> Violations;

	UFUNCTION(Category="Verdandi|Item", BlueprintCallable)
	virtual FString GetItemName() const PURE_VIRTUAL(UVerdandiItem::GetItemName, return "Unknown";)

	UFUNCTION(Category="Verdandi|Item", BlueprintCallable)
	virtual FText GetLabelText() const { return FText::FromString(GetItemName()); }

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
	FString GetItemDir() const;

	UFUNCTION(Category="Verdandi|Item", BlueprintCallable)
	FString GetItemPath() const;
	
	UFUNCTION(Category="Verdandi|Item", BlueprintCallable)
	FORCEINLINE UVerdandiTimeline* GetTimeline() const { return Timeline; }

	UFUNCTION(Category="Verdandi|Item", BlueprintCallable)
	FORCEINLINE UVerdandiItem* GetParent() const { return Parent; }

	UFUNCTION(Category="Verdandi|Item", BlueprintCallable)
	FORCEINLINE TArray<UVerdandiItem*> GetChildren() const { return Children; }

	void Refresh();
	virtual void FindChildren(TArray<TObjectPtr<UVerdandiItem>>& OutChildren) {}
	void FindViolations();

private:
	friend UVerdandiSource;

	UPROPERTY(Transient)
	TObjectPtr<UVerdandiTimeline> Timeline;
	
	UPROPERTY(Transient)
	TObjectPtr<UVerdandiItem> Parent = nullptr;

	UPROPERTY(Transient)
	TArray<TObjectPtr<UVerdandiItem>> Children;
};
