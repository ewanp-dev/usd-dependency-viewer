#include "TableHeader.h"

TableHeader::TableHeader(QWidget* parent)
{
    setFixedHeight(FIXED_BUTTON_SIZE_ + 6);
    setContentsMargins(8, 8, 8, 8);

    mainLayout_ = new QHBoxLayout(this);

    dependencyPath_ = new QLineEdit("/");
    dependencyPath_->setReadOnly(true);
    dependencyPath_->setFixedHeight(FIXED_BUTTON_SIZE_);
    dependencyPath_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    dependencyPath_->setProperty("class", "lineEdit");

    propertiesButton_ = initButton(":/icons/DarkMode/filter.png");
    homeButton_ = initButton(":/icons/DarkMode/home.png");
    upButton_ = initButton(":/icons/DarkMode/up.png");

    mainLayout_->addWidget(dependencyPath_);
    mainLayout_->addWidget(propertiesButton_);
    mainLayout_->addWidget(homeButton_);
    mainLayout_->addWidget(upButton_);
}

dvWidgets::AbstractButton* TableHeader::initButton(const std::string& iconPath)
{
    dvWidgets::AbstractButton* button = new dvWidgets::AbstractButton();

    button->setIcon(QIcon(iconPath.c_str()));
    button->setIconSize(FIXED_ICON_SIZE_);
    button->setFixedSize(FIXED_BUTTON_SIZE_, FIXED_BUTTON_SIZE_);
    button->setCursor(Qt::PointingHandCursor);
    button->setStyleSheet("background-color: transparent;");

    return button;
}

QLineEdit* TableHeader::dependencyPathWidget()
{
    return dependencyPath_;
}
