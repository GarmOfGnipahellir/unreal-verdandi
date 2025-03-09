// Fill out your copyright notice in the Description page of Project Settings.


#include "Violations/VerdandiViolation_MissingSequenceAsset.h"

#include "VerdandiItem.h"
#include "VerdandiTimeline.h"
#include "AssetRegistry/IAssetRegistry.h"

bool UVerdandiViolation_MissingSequenceAsset::TryFix(bool bIsDryRun) const
{
	FAssetData AssetData = IAssetRegistry::Get()->GetAssetByObjectPath(Item->GetItemPath());
	if ((!AssetData.IsValid() || AssetData.AssetClassPath != ULevelSequence::StaticClass()->GetClassPathName()) && bIsDryRun) return false;
	return true;
}
