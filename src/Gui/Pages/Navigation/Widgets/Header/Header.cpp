#include "Header.h"

#include <QPointF>

NavigationHeader::NavigationHeader(QWidget* parent)
{
    mainLayout_ = new QHBoxLayout(this);
    mainLayout_->setContentsMargins(10, 5, 10, 5);

    resultsList_ = new dvWidgets::AbstractButton();
    resultsList_->setFixedWidth(100);
    resultsList_->setSizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);

    sort_ = new dvWidgets::AbstractButton();
    sort_->setSizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
    sort_->setIconFromImage(":icons/filter.png");

    properties_ = new dvWidgets::AbstractButton();
    properties_->setSizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
    properties_->setIconFromImage(":icons/properties.png");

    resultsDropdown_ = new ResultsDropdownWidget();
    sortDropdown_ = new SortDropdownWidget();
    propertiesDropdown_ = new PropertiesDropdownWidget();

    connect(resultsList_, &dvWidgets::AbstractButton::clicked, this, [this]() {
        showDropdown_(resultsList_, resultsDropdown_);
    });

    connect(sort_, &dvWidgets::AbstractButton::clicked, this, [this]() {
        showDropdown_(sort_, sortDropdown_, 200);
    });

    connect(properties_, &dvWidgets::AbstractButton::clicked, this, [this]() {
        showDropdown_(properties_, propertiesDropdown_, 100);
    });

    mainLayout_->addWidget(resultsList_);
    mainLayout_->addStretch(1);
    mainLayout_->addWidget(sort_);
    mainLayout_->addWidget(properties_);
}

void NavigationHeader::showDropdown_(dvWidgets::AbstractButton* button, QWidget* dropdown, int shift)
{
    QPointF pos = button->mapToGlobal(button->rect().bottomLeft());
    if (shift > 0)
    {
        int posX = pos.x() - shift;
        pos.setX(posX);
    }
    dropdown->move(pos.x(), pos.y());
    dropdown->show();
}
