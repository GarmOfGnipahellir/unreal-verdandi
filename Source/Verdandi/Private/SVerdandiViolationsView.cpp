// Fill out your copyright notice in the Description page of Project Settings.


#include "SVerdandiViolationsView.h"

#include "SlateOptMacros.h"
#include "VerdandiEditor.h"
#include "VerdandiViolation.h"


void SVerdandiViolationsView::Construct(const FArguments& InArgs, TSharedPtr<FVerdandiEditor> InEditor)
{
	EditorPtr = InEditor;

	this->ChildSlot
	[
		SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.FillHeight(1)
		[
			SAssignNew(ListView, SListViewType)
			.ListItemsSource(&FoundViolations)
			.OnGenerateRow(this, &SVerdandiViolationsView::OnGenerateRow)
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
	return SNew(STableRow<FItemTypePtr>, TableViewBase)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.VAlign(VAlign_Center)
			.FillWidth(1)
			[
				SNew(STextBlock).Text(InViolation->GetLabelText())
			]
			+ SHorizontalBox::Slot()
			.AutoWidth()
			[
				SNew(SButton)
				.Text(FText::FromString("Fix"))
				.OnReleased(FSimpleDelegate::CreateLambda([InViolation]()
				{
					InViolation->TryFix();
				}))
			]
		];
}
