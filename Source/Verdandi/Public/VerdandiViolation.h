// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "VerdandiViolation.generated.h"

class UVerdandiTimeline;
class UVerdandiItem;

UENUM(BlueprintType)
enum class EViolationLevel : uint8
{
	Warning,
	Error,
};

/**
 * 
 */
UCLASS(Blueprintable, Abstract)
class VERDANDI_API UVerdandiViolation : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UVerdandiItem> Item;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Label;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EViolationLevel Level;

	UVerdandiViolation();

	virtual FText GetLabelText() const { return Label; }
	virtual FText GetDescription() const { return Description; }
	virtual EViolationLevel GetLevel() const { return Level; }

	virtual bool TryFix(bool bIsDryRun = false) { return BP_TryFix(bIsDryRun); }

	UVerdandiTimeline* GetTimeline() const;
	FText GetFromText() const;

protected:
	UFUNCTION(Category="Verdandi|Violation", BlueprintNativeEvent, DisplayName="Try Fix")
	bool BP_TryFix(bool bIsDryRun = false);
	bool BP_TryFix_Implementation(bool bIsDryRun = false) { return true; }
};
