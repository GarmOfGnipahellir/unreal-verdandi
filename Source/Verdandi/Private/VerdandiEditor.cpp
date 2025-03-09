// Fill out your copyright notice in the Description page of Project Settings.


#include "VerdandiEditor.h"

#include "SVerdandiItemsView.h"
#include "SVerdandiViolationsView.h"
#include "VerdandiTimeline.h"
#include "VerdandiViolation.h"

const FName ItemsId = "Items";
const FName ViolationsId = "Violations";
const FName DetailsId = "Details";


void FVerdandiEditor::Initialize(
	const EToolkitMode::Type InMode,
	const TSharedPtr<IToolkitHost>& InToolkitHost,
	UVerdandiTimeline* InVerdandiTimeline
)
{
	VerdandiTimelineEdited = InVerdandiTimeline;

	ItemsView = SNew(SVerdandiItemsView, SharedThis(this));
	ViolationsView = SNew(SVerdandiViolationsView, SharedThis(this));

	FPropertyEditorModule& PropertyEditorModule = FModuleManager::Get().GetModuleChecked<FPropertyEditorModule>(
		"PropertyEditor"
	);

	FDetailsViewArgs DetailsViewArgs;
	DetailsViewArgs.bAllowSearch = true;
	DetailsViewArgs.bLockable = false;
	DetailsViewArgs.bUpdatesFromSelection = false;
	DetailsViewArgs.NameAreaSettings = FDetailsViewArgs::HideNameArea;

	DetailsView = PropertyEditorModule.CreateDetailView(DetailsViewArgs);
	DetailsView->SetObject(VerdandiTimelineEdited);
	DetailsView->OnFinishedChangingProperties().AddSP(this, &FVerdandiEditor::OnFinishedChangingProperties);

	const TSharedRef<FTabManager::FLayout> StandaloneDefaultLayout = FTabManager::NewLayout(
			"Standalone_VerdandiEditor_Layout_v0.2"
		)
		->AddArea(
			FTabManager::NewPrimaryArea()
			->SetOrientation(Orient_Horizontal)
			->Split(
				FTabManager::NewStack()
				->SetSizeCoefficient(1.0f)
				->SetHideTabWell(true)
				->AddTab(ItemsId, ETabState::OpenedTab)
			)
			->Split(
				FTabManager::NewStack()
				->SetSizeCoefficient(1.0f)
				->SetHideTabWell(true)
				->AddTab(ViolationsId, ETabState::OpenedTab)
			)
			->Split(
				FTabManager::NewStack()
				->SetSizeCoefficient(1.0f)
				->SetHideTabWell(true)
				->AddTab(DetailsId, ETabState::OpenedTab)
			)
		);

	const FName VerdandiEditorAppName = "VerdandiEditorApp";
	InitAssetEditor(
		InMode,
		InToolkitHost,
		VerdandiEditorAppName,
		StandaloneDefaultLayout,
		true,
		true,
		InVerdandiTimeline
	);
}

void FVerdandiEditor::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	WorkspaceMenuCategory = InTabManager->AddLocalWorkspaceMenuCategory(FText::FromString("Verdandi Editor"));
	const TSharedRef<FWorkspaceItem>& WorkspaceMenuCategoryRef = WorkspaceMenuCategory.ToSharedRef();

	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);

	InTabManager->RegisterTabSpawner(
			ItemsId,
			FOnSpawnTab::CreateSP(this, &FVerdandiEditor::SpawnTab_Items)
		)
		.SetDisplayName(FText::FromString("Items"))
		.SetGroup(WorkspaceMenuCategoryRef);

	InTabManager->RegisterTabSpawner(
			ViolationsId,
			FOnSpawnTab::CreateSP(this, &FVerdandiEditor::SpawnTab_Violations)
		)
		.SetDisplayName(FText::FromString("Violations"))
		.SetGroup(WorkspaceMenuCategoryRef);

	InTabManager->RegisterTabSpawner(
			DetailsId,
			FOnSpawnTab::CreateSP(this, &FVerdandiEditor::SpawnTab_Details)
		)
		.SetDisplayName(FText::FromString("Details"))
		.SetGroup(WorkspaceMenuCategoryRef);
}

void FVerdandiEditor::UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	InTabManager->UnregisterTabSpawner(DetailsId);
	InTabManager->UnregisterTabSpawner(ItemsId);

	FAssetEditorToolkit::UnregisterTabSpawners(InTabManager);
}

void FVerdandiEditor::AddReferencedObjects(FReferenceCollector& Collector)
{
	Collector.AddReferencedObject(VerdandiTimelineEdited);
}

FName FVerdandiEditor::GetToolkitFName() const
{
	return "VerdandiEditor";
}

FText FVerdandiEditor::GetBaseToolkitName() const
{
	return FText::FromString("Verdandi Editor");
}

FLinearColor FVerdandiEditor::GetWorldCentricTabColorScale() const
{
	return FLinearColor::White;
}

FString FVerdandiEditor::GetWorldCentricTabPrefix() const
{
	return "Verdandi ";
}

void FVerdandiEditor::OnClose()
{
	FAssetEditorToolkit::OnClose();
}

void FVerdandiEditor::Refresh()
{
	ItemsView->Refresh();
	ViolationsView->Refresh();
}

void FVerdandiEditor::SetSelectedItems(TArray<TObjectPtr<UVerdandiItem>> InItems)
{
	SelectedItems = InItems;
	ViolationsView->FoundViolations.Empty();
	for (auto Item : SelectedItems)
	{
		ViolationsView->FoundViolations.Append(Item->Violations);
	}
	ViolationsView->ListView->RequestListRefresh();
}

void FVerdandiEditor::OnFinishedChangingProperties(const FPropertyChangedEvent& PropertyChangedEvent)
{
	Refresh();
}

TSharedRef<SDockTab> FVerdandiEditor::SpawnTab_Items(const FSpawnTabArgs& Args)
{
	return SNew(SDockTab)
		.Label(FText::FromString("Item"))
		[
			ItemsView.ToSharedRef()
		];
}

TSharedRef<SDockTab> FVerdandiEditor::SpawnTab_Violations(const FSpawnTabArgs& Args)
{
	return SNew(SDockTab)
		.Label(FText::FromString("Violations"))
		[
			ViolationsView.ToSharedRef()
		];
}

TSharedRef<SDockTab> FVerdandiEditor::SpawnTab_Details(const FSpawnTabArgs& Args)
{
	return SNew(SDockTab)
		.Label(FText::FromString("Details"))
		[
			DetailsView.ToSharedRef()
		];
}
