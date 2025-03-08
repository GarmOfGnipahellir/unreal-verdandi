// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class SVerdandiItemsView;
class UVerdandiTimeline;
/**
 * 
 */
class VERDANDI_API FVerdandiEditor
	: public FAssetEditorToolkit, public FGCObject, public FSelfRegisteringEditorUndoClient
{
public:
	void Initialize(
		const EToolkitMode::Type InMode,
		const TSharedPtr<IToolkitHost>& InToolkitHost,
		UVerdandiTimeline* InVerdandiTimeline
	);

	const UVerdandiTimeline* GetVerdandiTimeline() const { return VerdandiTimelineEdited; }

	virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;
	virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;

	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;
	virtual FString GetReferencerName() const override { return "FVerdandiEditor"; }

	virtual FName GetToolkitFName() const override;
	virtual FText GetBaseToolkitName() const override;
	virtual FLinearColor GetWorldCentricTabColorScale() const override;
	virtual FString GetWorldCentricTabPrefix() const override;
	virtual void OnClose() override;

protected:
	TSharedPtr<SVerdandiItemsView> ItemsView;
	TSharedPtr<IDetailsView> DetailsView;

	TObjectPtr<UVerdandiTimeline> VerdandiTimelineEdited = nullptr;

	TSharedRef<SDockTab> SpawnTab_Items(const FSpawnTabArgs& Args);
	TSharedRef<SDockTab> SpawnTab_Violations(const FSpawnTabArgs& Args);
	TSharedRef<SDockTab> SpawnTab_Details(const FSpawnTabArgs& Args);
};
