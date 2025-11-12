#include "Header.h"
#include <QHBoxLayout>
#include <Gui/MainWindow/Globals.h>

// TODO Add in connections
// TODO Update hader to reflect latest interface updates

Header::Header() 
{
    setFixedHeight(FIXED_HEADER_HEIGHT_);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    setAttribute(Qt::WidgetAttribute::WA_StyledBackground, true);

    mainLayout_ = new QHBoxLayout(this);

    homeButton_ = initButton("", ":/icons/DarkMode/leaf_colored.png");
    homeButton_->setProperty("class", "HomeButton");
    homeButton_->setStyleSheet("background-color: transparent;");
    homeButton_->setIconSize(QSize(FIXED_BUTTON_HEIGHT_, FIXED_BUTTON_HEIGHT_));

    visButton_ = initButton(" Visualization", ":/icons/DarkMode/graph.png");
    dependenciesButton_ = initButton(" Dependencies List", ":/icons/DarkMode/list.png");
    assetButton_ = initButton(" Asset View", ":/icons/DarkMode/asset.png");
    settingsButton_ = initButton(" Settings", ":/icons/DarkMode/settings.png");

    mainLayout_->addWidget(homeButton_);
    mainLayout_->addWidget(visButton_);
    mainLayout_->addWidget(dependenciesButton_);
    mainLayout_->addWidget(assetButton_);
    mainLayout_->addStretch();
    mainLayout_->addWidget(settingsButton_);

    setProperty("class", "WindowHeader");
}

dvWidgets::AbstractButton* Header::initButton(const std::string& text, const std::string& iconPath)
{
    /**
     * @brief Sets up a header button with default properties
     * to avoid boilerplate code
     */

    dvWidgets::AbstractButton* button = new dvWidgets::AbstractButton();

    button->setFixedHeight(FIXED_BUTTON_HEIGHT_);
    button->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    button->adjustSize();
    button->setText(text.c_str());
    button->setIcon(QIcon(iconPath.c_str()));
    button->setIconSize(FIXED_ICON_SIZE_);
    button->setCursor(Qt::PointingHandCursor);
    button->setProperty("class", "HeaderButton");

    QFont headerButtonFont = button->font();
    headerButtonFont.setPointSize(FIXED_FONT_SIZE_);

    return button;
}

dvWidgets::AbstractButton* Header::homeButton()
{
    return homeButton_;
}

dvWidgets::AbstractButton* Header::visualizationButton()
{
    return visButton_;
}

dvWidgets::AbstractButton* Header::dependenciesButton()
{
    return dependenciesButton_;
}

dvWidgets::AbstractButton* Header::assetButton()
{
    return assetButton_;
}

dvWidgets::AbstractButton* Header::settingsButton()
{
    return settingsButton_;
}
