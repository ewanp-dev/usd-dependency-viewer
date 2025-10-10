#include "Properties.h"
#include <QVBoxLayout>

PropertiesDropdownWidget::PropertiesDropdownWidget(QWidget *parent) {
    setWindowFlags(Qt::WindowFlags(windowFlags() | Qt::WindowType::Popup));
    
    QVBoxLayout *layout = new QVBoxLayout(this);
    checkName_ = new QCheckBox("File Name");
    checkPath_ = new QCheckBox("File Path");
    checkSize_ = new QCheckBox("File Size");
    checkExtension_ = new QCheckBox("File Extension");
    checkModified_ = new QCheckBox("Date Modified");

    checkName_->setCheckState(Qt::CheckState::Checked);

    layout->addWidget(checkName_);
    layout->addWidget(checkPath_);
    layout->addWidget(checkSize_);
    layout->addWidget(checkExtension_);
    layout->addWidget(checkModified_);
}
