// Copyright Epic Games, Inc. All Rights Reserved.

#include "VerdandiModule.h"

#define LOCTEXT_NAMESPACE "Verdandi"

void FVerdandiModule::StartupModule() {}

void FVerdandiModule::ShutdownModule() {}

TArray<TSubclassOf<UVerdandiViolation>> FVerdandiModule::GetViolationTypes()
{
	TArray<TSubclassOf<UVerdandiViolation>> Result;
	for (TObjectIterator<UClass> It; It; ++It)
	{
		UClass* Class = *It;
		if (Class->HasAnyClassFlags(CLASS_Abstract)) continue;
		if (!Class->IsChildOf<UVerdandiViolation>()) continue;

		Result.Add(Class);
	}
	return Result;
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FVerdandiModule, Verdandi)
