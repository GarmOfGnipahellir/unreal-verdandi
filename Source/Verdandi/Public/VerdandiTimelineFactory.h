// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Factories/Factory.h"
#include "VerdandiTimelineFactory.generated.h"

/**
 * 
 */
UCLASS()
class VERDANDI_API UVerdandiTimelineFactory : public UFactory
{
	GENERATED_BODY()

public:
	UVerdandiTimelineFactory(const FObjectInitializer& ObjectInitializer);
	
	virtual UObject* FactoryCreateNew(
		UClass* InClass,
		UObject* InParent,
		FName InName,
		EObjectFlags Flags,
		UObject* Context,
		FFeedbackContext* Warn
	) override;
	virtual bool ShouldShowInNewMenu() const override;
};
