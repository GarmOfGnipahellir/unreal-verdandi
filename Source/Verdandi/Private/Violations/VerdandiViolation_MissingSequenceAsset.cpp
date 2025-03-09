// Fill out your copyright notice in the Description page of Project Settings.


#include "Violations/VerdandiViolation_MissingSequenceAsset.h"

#include "IAssetTools.h"
#include "VerdandiItem.h"
#include "VerdandiTimeline.h"
#include "AssetRegistry/IAssetRegistry.h"

bool UVerdandiViolation_MissingSequenceAsset::TryFix(bool bIsDryRun)
{
	FAssetData AssetData = IAssetRegistry::Get()->GetAssetByObjectPath(Item->GetItemPath());
	if (!AssetData.IsValid())
	{
		if (bIsDryRun)
		{
			Description = FText::FromString("Asset does not exist.");
			return false;
		}

		IAssetTools::Get().CreateAsset(Item->GetItemName(), Item->GetItemDir(), ULevelSequence::StaticClass(), nullptr);
	}
	if (AssetData.AssetClassPath != ULevelSequence::StaticClass()->GetClassPathName())
	{
		Description = FText::FromString("Asset exists but is not a Level Sequence.");
		return false;
	}
	return true;
}
