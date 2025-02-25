// Fill out your copyright notice in the Description page of Project Settings.

#include "AssetDefinition_VerdandiTimeline.h"

#include "VerdandiTimeline.h"
#include "VerdandiEditor.h"

FText UAssetDefinition_VerdandiTimeline::GetAssetDisplayName() const
{
	return FText::FromString("Verdandi Timeline");
}

FLinearColor UAssetDefinition_VerdandiTimeline::GetAssetColor() const
{
	return FColor::Purple;
}

TSoftClassPtr<UObject> UAssetDefinition_VerdandiTimeline::GetAssetClass() const
{
	return UVerdandiTimeline::StaticClass();
}

TConstArrayView<FAssetCategoryPath> UAssetDefinition_VerdandiTimeline::GetAssetCategories() const
{
	static const FAssetCategoryPath Categories[] = {EAssetCategoryPaths::Cinematics};
	return Categories;
}

EAssetCommandResult UAssetDefinition_VerdandiTimeline::OpenAssets(const FAssetOpenArgs& OpenArgs) const
{
	for (UVerdandiTimeline* VerdandiTimeline : OpenArgs.LoadObjects<UVerdandiTimeline>())
	{
		const TSharedRef<FVerdandiEditor> VerdandiTimelineEditor = MakeShared<FVerdandiEditor>();
		VerdandiTimelineEditor->Initialize(EToolkitMode::Standalone, OpenArgs.ToolkitHost, VerdandiTimeline);
	}
	return EAssetCommandResult::Handled;
}
