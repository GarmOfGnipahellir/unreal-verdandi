// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class UVerdandiTimeline;
/**
 * 
 */
class VERDANDI_API FVerdandiEditor
	: public FAssetEditorToolkit, public FGCObject
{
public:
	void Initialize(
		const EToolkitMode::Type InMode,
		const TSharedPtr<IToolkitHost>& InToolkitHost,
		UVerdandiTimeline* InVerdandiTimeline
	);

	virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;
	virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;

	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;
	virtual FString GetReferencerName() const override { return "FVerdandiEditor"; }

	virtual FName GetToolkitFName() const override;
	virtual FText GetBaseToolkitName() const override;
	virtual FLinearColor GetWorldCentricTabColorScale() const override;
	virtual FString GetWorldCentricTabPrefix() const override;

protected:
	TSharedPtr<IDetailsView> AssetDetailsWidget;

	TObjectPtr<UVerdandiTimeline> VerdandiTimelineEdited = nullptr;

	TSharedRef<SDockTab> SpawnTab_Items(const FSpawnTabArgs& Args);
	TSharedRef<SDockTab> SpawnTab_Violations(const FSpawnTabArgs& Args);
	TSharedRef<SDockTab> SpawnTab_Details(const FSpawnTabArgs& Args);
};
