
#include "DependenciesList.h"

DependenciesListPage::DependenciesListPage(QWidget* parent)
{
    mainLayout_ = new QVBoxLayout(this);

    pageLabel_ = new QLabel("Asset View Page");

    mainLayout_->addWidget(pageLabel_);
}
