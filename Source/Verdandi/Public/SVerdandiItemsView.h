// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class UVerdandiTimeline;
class UVerdandiItem;
class UVerdandiSource;
class FVerdandiEditor;

typedef TObjectPtr<UVerdandiItem> FVerdandiItemPtr;

class VERDANDI_API SVerdandiItemsView : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SVerdandiItemsView) {}
	SLATE_END_ARGS()

	static FName ColumnItemLabel;
	static FName ColumnStatus;
	static FName ColumnPath;

	void Construct(const FArguments& InArgs, TSharedPtr<FVerdandiEditor> InVerdandiEditor);

	void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;

	void Refresh();

protected:
	typedef STreeView<FVerdandiItemPtr> STreeViewType;

	TWeakPtr<FVerdandiEditor> VerdandiEditorPtr;

	TSharedPtr<SHeaderRow> HeaderRow;
	TSharedPtr<STreeViewType> TreeView;

	TSharedRef<ITableRow> OnGenerateRow(FVerdandiItemPtr InItem, const TSharedRef<STableViewBase>& InOwnerTable);
	void OnGetChildren(FVerdandiItemPtr InItem, TArray<FVerdandiItemPtr>& OutChildren);
	void OnSelectionChanged(FVerdandiItemPtr VerdandiItem, ESelectInfo::Type Arg);
	EVisibility ThrobberVisibility() const;

	struct FFindItemsTask
	{
		TObjectPtr<UVerdandiTimeline> Timeline;
		
		static const TCHAR* GetTaskName()
		{
			return TEXT("FFindItemsTask");
		}
		
		FORCEINLINE static TStatId GetStatId()
		{
			RETURN_QUICK_DECLARE_CYCLE_STAT(FFindRootItemsTask, STATGROUP_TaskGraphTasks);
		}

		static ENamedThreads::Type GetDesiredThread()
		{
			return ENamedThreads::AnyThread;
		}

		static ESubsequentsMode::Type GetSubsequentsMode()
		{
			return ESubsequentsMode::TrackSubsequents;
		}

		void DoTask(ENamedThreads::Type CurrentThread, const FGraphEventRef& CompletionGraphEvent);
	};

	bool bFindingItems = false;
	FGraphEventArray FindItemsEvents;
	TArray<FVerdandiItemPtr> RootItemsFound;

	void FindItems();
	bool FindItemsComplete();

private:
	friend FVerdandiEditor;
};

class SVerdandiItemRow : public SMultiColumnTableRow<FVerdandiItemPtr>
{
public:
	SLATE_BEGIN_ARGS(SVerdandiItemRow) {}
		SLATE_ARGUMENT(FVerdandiItemPtr, Item)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& OwnerTableView);

	virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& InColumnName) override;

	const FSlateBrush* StatusImage() const;
	EVisibility StatusVisibility() const;
	TSharedPtr<IToolTip> StatusTooltip() const;

protected:
	FVerdandiItemPtr Item;
};
