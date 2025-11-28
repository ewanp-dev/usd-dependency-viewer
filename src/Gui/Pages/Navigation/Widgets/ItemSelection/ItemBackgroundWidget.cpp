#include "ItemBackgroundWidget.h"

ItemBackgroundWidget::ItemBackgroundWidget(QWidget* parent)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setContentsMargins(0, 0, 0, 0);

    auto* container = new QWidget(this);
    auto* layout = new QVBoxLayout(this);

    mainLayout_ = new QVBoxLayout(container);
    mainLayout_->setContentsMargins(0, 0, 0, 0);

    initHeader();
    initBody();

    mainLayout_->addLayout(headerLayout_);
    mainLayout_->addSpacing(8);
    mainLayout_->addWidget(itemArea_);

    layout->addWidget(container);
    layout->setContentsMargins(0, 8, 8, 0);
    container->setAttribute(Qt::WidgetAttribute::WA_StyledBackground, true);
    container->setProperty("class", "standardWidget");
    container->setStyleSheet(
        "border-top-left-radius: 4px;"
        "border-top-right-radius: 4px;"
    );
    container->setContentsMargins(12, 12, 12, 12);
}

void ItemBackgroundWidget::initHeader()
{
    headerLayout_ = new QHBoxLayout();
    headerLayout_->setContentsMargins(0, 0, 0, 0);

    searchBar_ = new QLineEdit();
    searchBar_->setPlaceholderText("Search...");
    
    filterButton_ = initButton(":/icons/DarkMode/jug.png");
    homeButton_ = initButton(":/icons/DarkMode/home.png");
    upButton_ = initButton(":/icons/DarkMode/up.png");

    headerLayout_->addWidget(searchBar_);
    headerLayout_->addSpacing(4);
    headerLayout_->addWidget(filterButton_);
    headerLayout_->addSpacing(4);
    headerLayout_->addWidget(homeButton_);
    headerLayout_->addSpacing(4);
    headerLayout_->addWidget(upButton_);
}

dvWidgets::AbstractButton* ItemBackgroundWidget::initButton(const std::string& iconPath)
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

void ItemBackgroundWidget::initBody()
{
    itemArea_ = new ItemListWidget();
}

ItemListWidget* ItemBackgroundWidget::getListWidget()
{
    return itemArea_;
}

void ItemBackgroundWidget::setActivePath(NodePath nodePath)
{
     
}


dvWidgets::AbstractButton* ItemBackgroundWidget::getFiltersButton()
{
    return filterButton_;
}

dvWidgets::AbstractButton* ItemBackgroundWidget::getHomeButton()
{
    return homeButton_;
}

dvWidgets::AbstractButton* ItemBackgroundWidget::getNavigationButton()
{
    return upButton_;
}
