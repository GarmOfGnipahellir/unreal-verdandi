// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "VerdandiItem.h"

class FVerdandiEditor;

typedef TObjectPtr<UVerdandiItem> FVerdandiItemPtr;

class VERDANDI_API SVerdandiItemsView : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SVerdandiItemsView) {}
	SLATE_END_ARGS()

	static FName ColumnItemLabel;
	static FName ColumnStatus;

	void Construct(const FArguments& InArgs, TSharedPtr<FVerdandiEditor> InVerdandiEditor);

protected:
	typedef FVerdandiItemPtr FItemTypePtr;
	typedef STreeView<FItemTypePtr> STreeViewType;

	TWeakPtr<FVerdandiEditor> VerdandiEditorPtr;

	TSharedPtr<SHeaderRow> HeaderRow;
	TSharedPtr<STreeViewType> TreeView;
	TArray<FItemTypePtr> ItemsFound;

	TSharedRef<ITableRow> OnGenerateRow(FItemTypePtr InItem, const TSharedRef<STableViewBase>& InOwnerTable);
	void OnGetChildren(FItemTypePtr InItem, TArray<FItemTypePtr>& OutChildren);
};

class SVerdandiItemRow : public SMultiColumnTableRow<FVerdandiItemPtr>
{
public:
	SLATE_BEGIN_ARGS(SVerdandiItemRow) {}
		SLATE_ARGUMENT(FVerdandiItemPtr, Item)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& OwnerTableView);

	virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& InColumnName) override;
	
	EVisibility StatusVisibility() const;

protected:
	FVerdandiItemPtr Item;
};
