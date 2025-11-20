
#include "DependenciesList.h"

DependenciesListPage::DependenciesListPage(QWidget* parent)
{
    mainLayout_ = new QVBoxLayout(this);

    pageLabel_ = new QLabel("Dependencies List Page");

    mainLayout_->addWidget(pageLabel_);
}
