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
    container->setStyleSheet("border-radius: 4px;");
    container->setContentsMargins(12, 12, 12, 12);
}

void ItemBackgroundWidget::initHeader()
{
    headerLayout_ = new QHBoxLayout();
    headerLayout_->setContentsMargins(0, 0, 0, 0);

    searchBar_ = new QLineEdit();
    
    filterButton_ = new dvWidgets::AbstractButton();
    filterButton_->setFixedSize(QSize(30, 30));
    filterButton_->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    filterButton_->setStyleSheet("background-color: transparent;");
    filterButton_->setIcon(QIcon(":/icons/DarkMode/jug.png"));
    filterButton_->setIconSize(QSize(22, 22));

    headerLayout_->addWidget(searchBar_);
    headerLayout_->addWidget(filterButton_);
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
