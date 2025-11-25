#include "FilePropertiesPage.h"

FilePropertiesPage::FilePropertiesPage(QWidget* parent)
{
    mainLayout_ = new QVBoxLayout(this);

    pageLabel_ = new QLabel("File Properties Page");

    mainLayout_->addWidget(pageLabel_);
}
