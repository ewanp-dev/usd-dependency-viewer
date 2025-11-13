#include "Footer.h"

Footer::Footer(const std::string& dependencyPath, QWidget* parent)
{
    setProperty("class", "standardWidget");

    mainLayout_ = new QVBoxLayout(this);
    mainLayout_->setContentsMargins(2, 2, 2, 2);

    dependencyPath_ = new QLabel("Active File: ");
    dependencyDepth_ = new QLabel("Dependencies - 3914");
    softwareVersion_ = new QLabel("USD Depend - 0.0.1"); 

    mainLayout_->addWidget(dependencyPath_);
    mainLayout_->addWidget(dependencyDepth_);
    mainLayout_->addStretch();
    mainLayout_->addWidget(softwareVersion_);
}
