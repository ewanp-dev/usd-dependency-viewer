#include "Header.h"
#include <QHBoxLayout>
#include <Gui/MainWindow/Globals.h>

// TODO Add in connections
// TODO Update hader to reflect latest interface updates

Header::Header() {
    const int FIXED_HEADER_HEIGHT = 40;
    const int FIXED_BUTTON_HEIGHT = 26;
    const int FIXED_HEADER_FONT_SIZE = 10;

    setFixedHeight(FIXED_HEADER_HEIGHT);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    setAttribute(Qt::WidgetAttribute::WA_StyledBackground, true);

    mainLayout_ = new QHBoxLayout(this);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    mainLayout_->setContentsMargins(10, 0, 10, 0);

    homeButton_ = new dvWidgets::AbstractButton();
    homeButton_->setProperty("class", "HomeButton");
    homeButton_->setStyleSheet("background-color: transparent;");
    homeButton_->setFixedHeight(FIXED_BUTTON_HEIGHT);
    homeButton_->setFixedWidth(30);
    homeButton_->setIcon(QIcon(":/icons/DarkMode/leaf_colored.png"));
    homeButton_->setIconSize(QSize(FIXED_BUTTON_HEIGHT, FIXED_BUTTON_HEIGHT));
    homeButton_->setCursor(Qt::PointingHandCursor);

    // NOTE: Kinda hacky way to keep a specific font size for the header
    QFont headerButtonFont = homeButton_->font();
    headerButtonFont.setPointSize(FIXED_HEADER_FONT_SIZE);

    visButton_ = new dvWidgets::AbstractButton();
    visButton_->setProperty("class", "HeaderButton");
    visButton_->setFixedHeight(FIXED_BUTTON_HEIGHT);
    visButton_->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    visButton_->adjustSize();
    visButton_->setText(" Visualization");
    visButton_->setIcon(QIcon(":/icons/DarkMode/graph.png"));
    visButton_->setIconSize(QSize(FIXED_HEADER_FONT_SIZE + 4, FIXED_HEADER_FONT_SIZE + 4));
    visButton_->setFont(headerButtonFont);
    visButton_->setCursor(Qt::PointingHandCursor);

    dependenciesButton_ = new dvWidgets::AbstractButton();
    dependenciesButton_->setProperty("class", "HeaderButton");
    dependenciesButton_->setFixedHeight(FIXED_BUTTON_HEIGHT);
    dependenciesButton_->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    dependenciesButton_->adjustSize();
    dependenciesButton_->setText(" Dependencies List");
    dependenciesButton_->setIcon(QIcon(":/icons/DarkMode/list.png"));
    dependenciesButton_->setIconSize(QSize(FIXED_HEADER_FONT_SIZE + 4, FIXED_HEADER_FONT_SIZE + 4));
    dependenciesButton_->setFont(headerButtonFont);
    dependenciesButton_->setCursor(Qt::PointingHandCursor);

    assetButton_ = new dvWidgets::AbstractButton();
    assetButton_->setProperty("class", "HeaderButton");
    assetButton_->setFixedHeight(FIXED_BUTTON_HEIGHT);
    assetButton_->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    assetButton_->adjustSize();
    assetButton_->setText(" Asset View");
    assetButton_->setIcon(QIcon(":/icons/DarkMode/asset.png"));
    assetButton_->setIconSize(QSize(FIXED_HEADER_FONT_SIZE + 4, FIXED_HEADER_FONT_SIZE + 4));
    assetButton_->setFont(headerButtonFont);
    assetButton_->setCursor(Qt::PointingHandCursor);

    settingsButton_ = new dvWidgets::AbstractButton();
    settingsButton_->setProperty("class", "HeaderButton");
    settingsButton_->setFixedHeight(FIXED_BUTTON_HEIGHT);
    settingsButton_->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    settingsButton_->adjustSize();
    settingsButton_->setText("Settings");
    settingsButton_->setIcon(QIcon(":/icons/DarkMode/settings.png"));
    settingsButton_->setIconSize(QSize(FIXED_HEADER_FONT_SIZE + 4, FIXED_HEADER_FONT_SIZE + 4));
    settingsButton_->setFont(headerButtonFont);
    settingsButton_->setCursor(Qt::PointingHandCursor);

    mainLayout_->addWidget(homeButton_);
    mainLayout_->addWidget(visButton_);
    mainLayout_->addWidget(dependenciesButton_);
    mainLayout_->addWidget(assetButton_);
    mainLayout_->addStretch();
    mainLayout_->addWidget(settingsButton_);

    setProperty("class", "WindowHeader");
}


