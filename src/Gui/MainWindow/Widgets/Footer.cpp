#include "Footer.h"

Footer::Footer(const std::string& dependencyPath, QWidget* parent)
{
    // setProperty("class", "standardWidget");
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    setFixedHeight(40);
    setContentsMargins(0, 0, 0, 0);

    QVBoxLayout* someLayout = new QVBoxLayout(this);

    QWidget* centralWidget = new QWidget();
    centralWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    centralWidget->setFixedHeight(24);

    centralWidget->setProperty("class", "standardWidget");
    centralWidget->setContentsMargins(20, 0, 20, 0);

    mainLayout_ = new QHBoxLayout(centralWidget);
    mainLayout_->setContentsMargins(0, 0, 0, 0);

    startText_ = new QLabel("Active File: ");
    dependencyPath_ = new QLabel(dependencyPath.c_str());
    dependencyDepth_ = new QLabel("Dependencies - 3914");
    softwareVersion_ = new QLabel("USD Depend - 0.0.1"); 

    mainLayout_->addWidget(startText_);
    mainLayout_->addWidget(dependencyPath_);
    mainLayout_->addWidget(dependencyDepth_);
    mainLayout_->addStretch();
    mainLayout_->addWidget(softwareVersion_);

    someLayout->addWidget(centralWidget);
}
