// Fill out your copyright notice in the Description page of Project Settings.


#include "SVerdandiItemsView.h"

#include "VerdandiEditor.h"
#include "VerdandiItem.h"
#include "VerdandiTimeline.h"
#include "VerdandiViolation.h"
#include "Widgets/Colors/SColorBlock.h"
#include "Widgets/Images/SThrobber.h"


FName SVerdandiItemsView::ColumnItemLabel = "ItemLabel";
FName SVerdandiItemsView::ColumnStatus = "Status";
FName SVerdandiItemsView::ColumnPath = "Path";

void SVerdandiItemsView::Construct(const FArguments& InArgs, TSharedPtr<FVerdandiEditor> InVerdandiEditor)
{
	VerdandiEditorPtr = InVerdandiEditor;

	if (InVerdandiEditor->GetTimeline()->Items.IsEmpty())
	{
		FindItems();
	}

	HeaderRow = SNew(SHeaderRow);
	HeaderRow->AddColumn(
		SHeaderRow::Column(ColumnStatus)
		.FixedWidth(24)
		.HAlignHeader(HAlign_Left)
		.VAlignHeader(VAlign_Center)
		.HAlignCell(HAlign_Center)
		.VAlignCell(VAlign_Center)
		.HeaderContentPadding(FMargin(4, 0, 0, 0))
		[
			SNew(SImage)
			.ColorAndOpacity(FSlateColor::UseForeground())
			.DesiredSizeOverride(FVector2D(16, 16))
			.Image(FAppStyle::Get().GetBrush("Icons.Alert.Solid"))
		]
	);
	HeaderRow->AddColumn(SHeaderRow::Column(ColumnItemLabel).DefaultLabel(FText::FromString("Item")));
	HeaderRow->AddColumn(SHeaderRow::Column(ColumnPath).DefaultLabel(FText::FromString("Path")));


	this->ChildSlot
	[
		SNew(SOverlay)
		+ SOverlay::Slot()
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.FillHeight(1)
			[
				SAssignNew(TreeView, STreeViewType)
				.TreeItemsSource(&InVerdandiEditor->GetTimeline()->Items)
				.HeaderRow(HeaderRow)
				.OnGenerateRow(this, &SVerdandiItemsView::OnGenerateRow)
				.OnGetChildren(this, &SVerdandiItemsView::OnGetChildren)
				.OnSelectionChanged(this, &SVerdandiItemsView::OnSelectionChanged)
			]
		]
		+ SOverlay::Slot()
		[
			SNew(SOverlay)
			.Visibility(this, &SVerdandiItemsView::ThrobberVisibility)
			+ SOverlay::Slot()
			[
				SNew(SColorBlock)
				.Color(FLinearColor(0, 0, 0, 0.5))
			]
			+ SOverlay::Slot()
			.HAlign(HAlign_Center)
			[
				SNew(SThrobber)
			]
		]
	];
}

void SVerdandiItemsView::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	SCompoundWidget::Tick(AllottedGeometry, InCurrentTime, InDeltaTime);

	if (bFindingItems && FindItemsComplete())
	{
		TreeView->RequestTreeRefresh();
		bFindingItems = false;
	}
}

void SVerdandiItemsView::Refresh()
{
	// RootItemsFound.Empty();
	// if (auto Source = VerdandiEditorPtr.Pin()->GetVerdandiTimeline()->Source)
	// {
	// 	Source->Refresh();
	// 	RootItemsFound = Source->GetRootItems();
	// }
	// TreeView->RequestTreeRefresh();
}

TSharedRef<ITableRow> SVerdandiItemsView::OnGenerateRow(
	FVerdandiItemPtr InItem,
	const TSharedRef<STableViewBase>& InOwnerTable
)
{
	return SNew(SVerdandiItemRow, InOwnerTable).Item(InItem);
}

void SVerdandiItemsView::OnGetChildren(FVerdandiItemPtr InItem, TArray<FVerdandiItemPtr>& OutChildren)
{
	OutChildren = InItem->GetChildren();
}

void SVerdandiItemsView::OnSelectionChanged(FVerdandiItemPtr VerdandiItem, ESelectInfo::Type Arg)
{
	VerdandiEditorPtr.Pin()->SetSelectedItems(TreeView->GetSelectedItems());
}

EVisibility SVerdandiItemsView::ThrobberVisibility() const
{
	if (bFindingItems)
	{
		return EVisibility::Visible;
	}
	return EVisibility::Hidden;
}

void SVerdandiItemsView::FFindItemsTask::DoTask(
	ENamedThreads::Type CurrentThread,
	const FGraphEventRef& CompletionGraphEvent
)
{
	Timeline->Items.Empty();
	Timeline->Source->Refresh();
	Timeline->Items.Append(Timeline->Source->GetRootItems());
}

void SVerdandiItemsView::FindItems()
{
	if (bFindingItems) return;

	FindItemsEvents.Add(
		TGraphTask<FFindItemsTask>::CreateTask(nullptr, ENamedThreads::Type::GameThread)
		.ConstructAndDispatchWhenReady(VerdandiEditorPtr.Pin()->GetTimeline())
	);
	bFindingItems = true;
}

bool SVerdandiItemsView::FindItemsComplete()
{
	for (auto& Task : FindItemsEvents)
	{
		if (!Task->IsComplete())
		{
			return false;
		}
	}
	return true;
}

void SVerdandiItemRow::Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& OwnerTableView)
{
	Item = InArgs._Item;

	SMultiColumnTableRow::Construct(SMultiColumnTableRow::FArguments(), OwnerTableView);
}

TSharedRef<SWidget> SVerdandiItemRow::GenerateWidgetForColumn(const FName& InColumnName)
{
	if (InColumnName == SVerdandiItemsView::ColumnItemLabel)
	{
		return SNew(SHorizontalBox)
			+ SHorizontalBox::Slot().AutoWidth().Padding(6, 0, 0, 0)
			[
				SNew(SExpanderArrow, SharedThis(this)).IndentAmount(12)
			]
			+ SHorizontalBox::Slot()
			.FillWidth(1)
			[
				SNew(STextBlock).Text(Item->GetLabelText())
			];
	}
	if (InColumnName == SVerdandiItemsView::ColumnStatus)
	{
		return SNew(SImage)
			.Image(this, &SVerdandiItemRow::StatusImage)
			//.Visibility(this, &SVerdandiItemRow::StatusVisibility)
			.ToolTip(this, &SVerdandiItemRow::StatusTooltip);
	}
	if (InColumnName == SVerdandiItemsView::ColumnPath)
	{
		return SNew(STextBlock)
			.Text(FText::FromString(Item->GetItemDir()))
			.Margin(FMargin(6, 0, 0, 0))
			.ColorAndOpacity(FLinearColor(1, 1, 1, 0.5f));
	}
	return SNew(STextBlock).Text(FText::FromString("Invalid Column"));
}

const FSlateBrush* SVerdandiItemRow::StatusImage() const
{
	FName BrushName = "Icons.Help";
	if (!Item->Violations.IsEmpty())
	{
		EViolationLevel HighestLevel = EViolationLevel::Warning;
		for (auto Violation : Item->Violations)
		{
			if (Violation->Level > HighestLevel)
			{
				HighestLevel = Violation->Level;
			}
		}
		switch (HighestLevel)
		{
		case EViolationLevel::Warning:
			BrushName = "Icons.Warning.Solid";
			break;
		case EViolationLevel::Error:
			BrushName = "Icons.Error.Solid";
			break;
		}
	}
	else
	{
		TOptional<EViolationLevel> HighestLevel;
		TQueue<UVerdandiItem*> Queue;
		for (auto Child : Item->GetChildren())
		{
			Queue.Enqueue(Child);
		}
		UVerdandiItem* QueueItem;
		while (Queue.Dequeue(QueueItem))
		{
			for (auto Violation : QueueItem->Violations)
			{
				if (!HighestLevel || Violation->Level > *HighestLevel)
				{
					HighestLevel = Violation->Level;
				}
			}
			for (auto Child : QueueItem->GetChildren())
			{
				Queue.Enqueue(Child);
			}
		}
		if (!HighestLevel)
		{
			BrushName = "None";
		}
		else
		{
			switch (*HighestLevel)
			{
			case EViolationLevel::Warning:
				BrushName = "Icons.WarningWithColor";
				break;
			case EViolationLevel::Error:
				BrushName = "Icons.ErrorWithColor";
				break;
			}
		}
	}
	return FAppStyle::Get().GetBrush(BrushName);
}

EVisibility SVerdandiItemRow::StatusVisibility() const
{
	if (Item->Violations.IsEmpty())
	{
		return EVisibility::Hidden;
	}
	return EVisibility::Visible;
}

TSharedPtr<IToolTip> SVerdandiItemRow::StatusTooltip() const
{
	FText ToolTipText;
	EViolationLevel HighestLevel = EViolationLevel::Warning;
	for (auto Violation : Item->Violations)
	{
		if (Violation->Level > HighestLevel)
		{
			HighestLevel = Violation->Level;
		}
	}
	switch (HighestLevel)
	{
	case EViolationLevel::Warning:
		ToolTipText = FText::FromString("Can be auto-fixed.");
		break;
	case EViolationLevel::Error:
		ToolTipText = FText::FromString("Not auto-fixable.");
		break;
	}
	return FSlateApplicationBase::Get().MakeToolTip(ToolTipText);
}
