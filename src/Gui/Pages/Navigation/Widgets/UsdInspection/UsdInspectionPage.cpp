#include "UsdInspectionPage.h"

UsdInspectionPage::UsdInspectionPage(QWidget* parent)
{
    mainLayout_ = new QVBoxLayout(this);

    pageLabel_ = new QLabel("Usd Inspection Page");

    mainLayout_->addWidget(pageLabel_);
}
