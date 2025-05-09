// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LevelSequence.h"
#include "VerdandiSource.h"
#include "UObject/Object.h"
#include "VerdandiTimeline.generated.h"


/**
 * 
 */
UCLASS(BlueprintType)
class VERDANDI_API UVerdandiTimeline : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<ULevelSequence> Target;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced)
	TObjectPtr<UVerdandiSource> Source;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, AdvancedDisplay, Transient)
	TArray<TObjectPtr<UVerdandiItem>> Items;

	FString GetRootDir() const;
};
