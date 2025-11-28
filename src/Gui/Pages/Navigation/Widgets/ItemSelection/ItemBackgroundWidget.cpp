#include "ItemBackgroundWidget.h"

ItemBackgroundWidget::ItemBackgroundWidget(QWidget* parent)
{
    setContentsMargins(0, 0, 0, 0);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    mainLayout_ = new QVBoxLayout(this);

}

void ItemBackgroundWidget::initHeader()
{
    headerLayout_ = new QHBoxLayout();

    searchBar_ = new QLineEdit();
    
    filterButton_ = new dvWidgets::AbstractButton();

    headerLayout_->addWidget(searchBar_);
    headerLayout_->addWidget(filterButton_);
}

void ItemBackgroundWidget::initBody()
{
    itemArea_ = new QScrollArea();
    itemArea_->setWidgetResizable(true);
    itemArea_->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    itemArea_->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
}
