// Fill out your copyright notice in the Description page of Project Settings.


#include "SVerdandiItemsView.h"

#include "VerdandiEditor.h"
#include "VerdandiItem.h"
#include "VerdandiTimeline.h"
#include "Misc/SourceLocationUtils.h"
#include "Styling/SlateIconFinder.h"


FName SVerdandiItemsView::ColumnItemLabel = "ItemLabel";
FName SVerdandiItemsView::ColumnStatus = "Status";

void SVerdandiItemsView::Construct(const FArguments& InArgs, TSharedPtr<FVerdandiEditor> InVerdandiEditor)
{
	VerdandiEditorPtr = InVerdandiEditor;

	ItemsFound = VerdandiEditorPtr.Pin()->GetVerdandiTimeline()->Source->GetRootItems();

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
	HeaderRow->AddColumn(SHeaderRow::Column(ColumnItemLabel).DefaultLabel(FText::FromString("Item Label")));

	this->ChildSlot
	[
		SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.FillHeight(1)
		[
			SAssignNew(TreeView, STreeViewType)
			.TreeItemsSource(&ItemsFound)
			.HeaderRow(HeaderRow)
			.OnGenerateRow(this, &SVerdandiItemsView::OnGenerateRow)
			.OnGetChildren(this, &SVerdandiItemsView::OnGetChildren)
			.OnSelectionChanged(this, &SVerdandiItemsView::OnSelectionChanged)
		]
	];
}

void SVerdandiItemsView::Refresh()
{
	ItemsFound.Empty();
	if (auto Source = VerdandiEditorPtr.Pin()->GetVerdandiTimeline()->Source)
	{
		Source->Refresh();
		ItemsFound = Source->GetRootItems();
	}
	TreeView->RequestTreeRefresh();
}

TSharedRef<ITableRow> SVerdandiItemsView::OnGenerateRow(
	FItemTypePtr InItem,
	const TSharedRef<STableViewBase>& InOwnerTable
)
{
	return SNew(SVerdandiItemRow, InOwnerTable).Item(InItem);
}

void SVerdandiItemsView::OnGetChildren(FItemTypePtr InItem, TArray<FItemTypePtr>& OutChildren)
{
	OutChildren = InItem->GetChildren();
}

void SVerdandiItemsView::OnSelectionChanged(TObjectPtr<UVerdandiItem> VerdandiItem, ESelectInfo::Type Arg)
{
	VerdandiEditorPtr.Pin()->SetSelectedItems(TreeView->GetSelectedItems());
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
		if (!Item->Violations.IsEmpty())
		{
			return SNew(SImage).Image(FAppStyle::Get().GetBrush("Icons.Error.Solid"));
		}
		return SNew(SImage)
			.Image(FAppStyle::Get().GetBrush("Icons.Error.Solid"))
			.Visibility(this, &SVerdandiItemRow::StatusVisibility);
	}
	return SNew(STextBlock).Text(FText::FromString("Invalid Column"));
}

EVisibility SVerdandiItemRow::StatusVisibility() const
{
	if (Item->Violations.IsEmpty())
	{
		return EVisibility::Hidden;
	}
	return EVisibility::Visible;
}
