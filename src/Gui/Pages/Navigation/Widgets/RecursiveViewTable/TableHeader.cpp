#include "TableHeader.h"

TableHeader::TableHeader(QWidget* parent)
{
    setProperty("class", "ClassStandardWidget");
    setFixedHeight(42);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    // setContentsMargins(0, 0, 0, 0);
    setStyleSheet(
        "border-radius: 4px;"
    );

    mainLayout_ = new QHBoxLayout(this);
    mainLayout_->setContentsMargins(6, 6, 12, 6);

    dependencyPath_ = new QLineEdit("/");
    dependencyPath_->setReadOnly(true);
    dependencyPath_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    dependencyPath_->setProperty("class", "lineEdit");

    propertiesButton_ = initButton(":/icons/DarkMode/filter.png");
    homeButton_ = initButton(":/icons/DarkMode/home.png");
    upButton_ = initButton(":/icons/DarkMode/up.png");

    mainLayout_->addWidget(dependencyPath_);
    // mainLayout_->addWidget(propertiesButton_);
    // mainLayout_->addWidget(homeButton_);
    // mainLayout_->addWidget(upButton_);
}

dvWidgets::AbstractButton* TableHeader::initButton(const std::string& iconPath)
{
    dvWidgets::AbstractButton* button = new dvWidgets::AbstractButton();

    button->setIcon(QIcon(iconPath.c_str()));
    button->setIconSize(FIXED_ICON_SIZE_);
    button->setFixedSize(FIXED_BUTTON_SIZE_, FIXED_BUTTON_SIZE_);
    button->setCursor(Qt::PointingHandCursor);
    button->setStyleSheet("background-color: transparent;");
    button->enableHoverEvent(false);

    return button;
}

QLineEdit* TableHeader::dependencyPathWidget()
{
    return dependencyPath_;
}

dvWidgets::AbstractButton* TableHeader::getPropertiesButton()
{
    return propertiesButton_;
}

dvWidgets::AbstractButton* TableHeader::getHomeButton()
{
    return homeButton_;
}

dvWidgets::AbstractButton* TableHeader::getNavigationButton()
{
    return upButton_;
}
