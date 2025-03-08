// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "VerdandiViolation.h"
#include "Modules/ModuleManager.h"


class FVerdandiModule : public IModuleInterface
{
public:
	static FVerdandiModule& Get()
	{
		return FModuleManager::LoadModuleChecked<FVerdandiModule>("Verdandi");
	}

	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	static TArray<TSubclassOf<UVerdandiViolation>> GetViolationTypes();
};
