#include "Footer.h"

#include <iostream>

Footer::Footer(const std::string& dependencyPath, int numDependencies, QWidget* parent)
{
    std::cout << numDependencies << '\n';
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    setContentsMargins(0, 0, 0, 0);
    setFixedHeight(40);

    QVBoxLayout* someLayout = new QVBoxLayout(this);
    QWidget* centralWidget  = new QWidget();

    centralWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    centralWidget->setFixedHeight(24);
    centralWidget->setProperty("class", "standardWidget");
    centralWidget->setContentsMargins(10, 0, 10, 0);

    mainLayout_ = new QHBoxLayout(centralWidget);
    mainLayout_->setContentsMargins(0, 0, 0, 0);

    startText_       = new QLabel("Active File: ");
    dependencyPath_  = new QLabel(dependencyPath.c_str());
    dependencyPath_->setStyleSheet("color: #ACFBE5;");
    QLabel* dependenciesPrecursor = new QLabel("Dependencies: ");
    dependencyDepth_ = new QLabel(std::to_string(numDependencies).c_str());
    dependencyDepth_->setStyleSheet("color: #DEC7FC;");
    softwareVersion_ = new QLabel("USD Depend - 0.0.1"); 

    mainLayout_->addWidget(startText_);
    mainLayout_->addWidget(dependencyPath_);
    mainLayout_->addSpacing(8);
    mainLayout_->addWidget(dependenciesPrecursor);
    mainLayout_->addWidget(dependencyDepth_);
    mainLayout_->addStretch();
    mainLayout_->addWidget(softwareVersion_);

    someLayout->addWidget(centralWidget);
}
