// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

class UVerdandiViolation;
class FVerdandiEditor;
/**
 * 
 */
class VERDANDI_API SVerdandiViolationsView : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SVerdandiViolationsView) {}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs, TSharedPtr<FVerdandiEditor> InEditor);

	void Refresh();

protected:
	typedef TObjectPtr<UVerdandiViolation> FItemTypePtr;
	typedef SListView<FItemTypePtr> SListViewType;

	TWeakPtr<FVerdandiEditor> EditorPtr;

	TSharedPtr<SListViewType> ListView;

	TArray<FItemTypePtr> FoundViolations;

	TSharedRef<ITableRow> OnGenerateRow(
		TObjectPtr<UVerdandiViolation> InViolation,
		const TSharedRef<STableViewBase>& TableViewBase
	);

private:
	friend FVerdandiEditor;
};
