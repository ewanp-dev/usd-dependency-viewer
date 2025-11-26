#include "Header.h"

#include <QHBoxLayout>
#include <Gui/MainWindow/Globals.h>
#include <Gui/Widgets/AbstractWidgetUtils.h>

Header::Header(QWidget* parent) 
{
    setFixedHeight(FIXED_HEADER_HEIGHT_);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    setAttribute(Qt::WidgetAttribute::WA_StyledBackground, true);
    setContentsMargins(0, 0, 0, 0);

    headerButtons_ = {};

    mainLayout_ = new QHBoxLayout(this);

    homeButton_ = initButton("", ":/icons/DarkMode/leaf_colored.png", false);
    homeButton_->setProperty("class", "HomeButton");
    homeButton_->setStyleSheet("background-color: transparent;");
    homeButton_->setIconSize(QSize(FIXED_BUTTON_HEIGHT_, FIXED_BUTTON_HEIGHT_));
    homeButton_->enableHoverEvent(false);
    homeButton_->setCheckable(false);

    visButton_          = initButton(" Visualization", ":/icons/DarkMode/graph.png");
    dependenciesButton_ = initButton(" Dependencies List", ":/icons/DarkMode/list.png");
    assetButton_        = initButton(" Asset View", ":/icons/DarkMode/asset.png");
    settingsButton_     = initButton("", ":/icons/DarkMode/settings.png");
    settingsButton_->setIconSize(QSize(FIXED_BUTTON_HEIGHT_ - 10, FIXED_BUTTON_HEIGHT_ - 10));
    settingsButton_->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    settingsButton_->setFixedWidth(FIXED_BUTTON_HEIGHT_);

    mainLayout_->addWidget(homeButton_);
    mainLayout_->addWidget(visButton_);
    mainLayout_->addSpacing(6);
    mainLayout_->addWidget(dependenciesButton_);
    mainLayout_->addSpacing(6);
    mainLayout_->addWidget(assetButton_);
    mainLayout_->addStretch();
    mainLayout_->addWidget(settingsButton_);

    setProperty("class", "WindowHeader");
}

dvWidgets::AbstractButton* Header::initButton(const std::string& text, const std::string& iconPath, bool enableSignals)
{
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

    if ( enableSignals )
    {
        // NOTE:
        //
        // Right now we don't want the home button to follow the signal rules so
        // I just put in this hacky method to get around it, should probably
        // build it into the interface utils function in the future

        headerButtons_.push_back(button);

        connect(button, &dvWidgets::AbstractButton::clicked, this, [this, button]() {
            dvWidgets::AbstractWidgetUtils::setSelectedButtonItem(headerButtons_, button); 
        });
    }

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
