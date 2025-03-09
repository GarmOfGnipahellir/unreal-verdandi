// Fill out your copyright notice in the Description page of Project Settings.


#include "SVerdandiViolationsView.h"

#include "SlateOptMacros.h"
#include "VerdandiEditor.h"
#include "VerdandiItem.h"
#include "VerdandiViolation.h"

FName SVerdandiViolationsView::ColumnType = "Type";
FName SVerdandiViolationsView::ColumnDescription = "Description";
FName SVerdandiViolationsView::ColumnFrom = "From";

void SVerdandiViolationsView::Construct(const FArguments& InArgs, TSharedPtr<FVerdandiEditor> InEditor)
{
	EditorPtr = InEditor;

	UToolMenus* ToolMenus = UToolMenus::Get();
	if (!ToolMenus->IsMenuRegistered("Verdandi.Violations.Context"))
	{
		UToolMenu* Menu = ToolMenus->RegisterMenu("Verdandi.Violations.Context");
		FToolMenuSection& Section = Menu->AddSection("Fix", FText::FromString("Fix"));
		Section.AddMenuEntry(
			"Fix",
			FText::FromString("Fix"),
			FText::FromString("Tries to fix selected violation(s)."),
			FSlateIcon(),
			FToolUIActionChoice(
				FExecuteAction::CreateLambda(
					[this]
					{
						for (auto Violation : ListView->GetSelectedItems())
						{
							Violation->TryFix();
						}
						TSharedPtr<FVerdandiEditor> Editor = EditorPtr.Pin();
						for (auto Item : Editor->GetSelectedItems())
						{
							Item->FindViolations();
						}
						Editor->SetSelectedItems(Editor->GetSelectedItems());
					}
				)
			)
		);
	}

	HeaderRow = SNew(SHeaderRow);
	HeaderRow->AddColumn(SHeaderRow::Column(ColumnType).DefaultLabel(FText::FromString("Violation")).FillWidth(0.5f));
	HeaderRow->AddColumn(SHeaderRow::Column(ColumnDescription).DefaultLabel(FText::FromString("Description")));
	HeaderRow->AddColumn(SHeaderRow::Column(ColumnFrom).DefaultLabel(FText::FromString("From")).FillWidth(0.25f));

	this->ChildSlot
	[
		SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.FillHeight(1)
		[
			SAssignNew(ListView, SListViewType)
			.ListItemsSource(&FoundViolations)
			.HeaderRow(HeaderRow)
			.OnGenerateRow(this, &SVerdandiViolationsView::OnGenerateRow)
			.OnContextMenuOpening(this, &SVerdandiViolationsView::OnContextMenuOpening)
		]
	];
}

void SVerdandiViolationsView::Refresh()
{
	ListView->RequestListRefresh();
}

TSharedRef<ITableRow> SVerdandiViolationsView::OnGenerateRow(
	TObjectPtr<UVerdandiViolation> InViolation,
	const TSharedRef<STableViewBase>& TableViewBase
)
{
	return SNew(SVerdandiViolationRow, TableViewBase).Violation(InViolation);
}

TSharedPtr<SWidget> SVerdandiViolationsView::OnContextMenuOpening()
{
	FToolMenuContext Context;

	UToolMenus* ToolMenus = UToolMenus::Get();
	UToolMenu* ToolMenu = ToolMenus->GenerateMenu("Verdandi.Violations.Context", Context);

	return ToolMenus->GenerateWidget(ToolMenu);
}

void SVerdandiViolationRow::Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& OwnerTableView)
{
	Violation = InArgs._Violation;

	SMultiColumnTableRow::Construct(SMultiColumnTableRow::FArguments(), OwnerTableView);
}

TSharedRef<SWidget> SVerdandiViolationRow::GenerateWidgetForColumn(const FName& InColumnName)
{
	if (InColumnName == SVerdandiViolationsView::ColumnType)
	{
		return SNew(STextBlock).Text(Violation->GetLabelText()).Margin(FMargin(6, 0, 0, 0));
	}
	if (InColumnName == SVerdandiViolationsView::ColumnDescription)
	{
		return SNew(STextBlock).Text(Violation->GetDescription()).Margin(FMargin(6, 0, 0, 0));
	}
	if (InColumnName == SVerdandiViolationsView::ColumnFrom)
	{
		return SNew(STextBlock).Text(Violation->GetFromText()).Margin(FMargin(6, 0, 0, 0));
	}
	return SNew(STextBlock).Text(FText::FromString("Invalid Column"));
}
