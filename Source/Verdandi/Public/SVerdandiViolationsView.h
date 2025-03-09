// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

class UVerdandiViolation;
class FVerdandiEditor;

typedef TObjectPtr<UVerdandiViolation> FVerdandiViolationPtr;

class VERDANDI_API SVerdandiViolationsView : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SVerdandiViolationsView) {}
	SLATE_END_ARGS()
	
	static FName ColumnType;
	static FName ColumnDescription;
	static FName ColumnFrom;

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs, TSharedPtr<FVerdandiEditor> InEditor);

	void Refresh();

protected:
	typedef SListView<FVerdandiViolationPtr> SListViewType;

	TWeakPtr<FVerdandiEditor> EditorPtr;

	TSharedPtr<SHeaderRow> HeaderRow;
	TSharedPtr<SListViewType> ListView;

	TArray<FVerdandiViolationPtr> FoundViolations;

	TSharedRef<ITableRow> OnGenerateRow(
		TObjectPtr<UVerdandiViolation> InViolation,
		const TSharedRef<STableViewBase>& TableViewBase
	);
	TSharedPtr<SWidget> OnContextMenuOpening();

private:
	friend FVerdandiEditor;
};

class SVerdandiViolationRow : public SMultiColumnTableRow<FVerdandiViolationPtr>
{
public:
	SLATE_BEGIN_ARGS(SVerdandiViolationRow) {}
		SLATE_ARGUMENT(FVerdandiViolationPtr, Violation)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& OwnerTableView);

	virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& InColumnName) override;

protected:
	FVerdandiViolationPtr Violation;
};
