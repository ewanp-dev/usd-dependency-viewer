#include "Sort.h"
#include <QHBoxLayout>

// TODO: Add in signal functions from Python branch

SortDropdownWidget::SortDropdownWidget(QWidget *parent) {
    setWindowFlags(Qt::WindowFlags(windowFlags() | Qt::WindowType::Popup));

    QHBoxLayout *layout = new QHBoxLayout(this);
    
    sortType_ = new QComboBox();
    sortRule_ = new QComboBox();
    clearSort_ = new AbstractButton();
    clearSort_->setText("Clear");

    typesList_ = {
        "File Name",
        "File Path",
        "File Size",
        "Extension",
        "Date Created",
        "Date Modified"
    };

    sortType_->addItems(typesList_);
    sortType_->setPlaceholderText("Text");
    sortRule_->addItems({"A->Z", "Z->A"});

    layout->addWidget(sortType_);
    layout->addWidget(sortRule_);
    layout->addWidget(clearSort_);
}
