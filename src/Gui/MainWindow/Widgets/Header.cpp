#include "Header.h"
#include <QHBoxLayout>
#include <Gui/MainWindow/Globals.h>

// TODO Add in connections
// TODO Update hader to reflect latest interface updates

Header::Header() {
    int FIXED_HEIGHT = 50;
    setFixedHeight(FIXED_HEIGHT);
    setAttribute(Qt::WidgetAttribute::WA_StyledBackground, true);

    mainLayout_ = new QHBoxLayout(this);
    QSpacerItem *spacer = new QSpacerItem(0, 0, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

    homeButton_ = new dvWidgets::AbstractButton();
    homeButton_->setText("Home");
    homeButton_->setSizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

    visButton_ = new dvWidgets::AbstractButton();
    visButton_->setText("Visualization");
    visButton_->setSizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

    dependenciesButton_ = new dvWidgets::AbstractButton();
    dependenciesButton_->setText("Dependencies List");
    dependenciesButton_->setSizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

    assetButton_ = new dvWidgets::AbstractButton();
    assetButton_->setText("Asset View");
    assetButton_->setSizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

    settingsButton_ = new dvWidgets::AbstractButton();
    settingsButton_->setText("Settings");
    settingsButton_->setSizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

    mainLayout_->addWidget(homeButton_, Qt::AlignmentFlag::AlignLeft);
    mainLayout_->addWidget(visButton_, Qt::AlignmentFlag::AlignLeft);
    mainLayout_->addWidget(dependenciesButton_, Qt::AlignmentFlag::AlignLeft);
    mainLayout_->addWidget(assetButton_, Qt::AlignmentFlag::AlignLeft);
    mainLayout_->addStretch();
    mainLayout_->addWidget(settingsButton_, Qt::AlignmentFlag::AlignRight);

    setProperty("class", "WindowHeader");
}


