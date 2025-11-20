#include "Tree.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

DependenciesTreeWidget::DependenciesTreeWidget(QWidget *parent) {
    setMinimumWidth(45);

    QVBoxLayout* layout = new QVBoxLayout(this);
    QHBoxLayout* topLayout = new QHBoxLayout();
    layout->setContentsMargins(15, 15, 15, 15);

    searchBar_ = new QLineEdit();
    searchBar_->setPlaceholderText("> Search...");
    searchBar_->setFixedHeight(25);

    filterButton_ = new dvWidgets::AbstractButton();
    filterButton_->setIconFromImage(":/icons/filter.png");
    filterButton_->setIconSize(QSize(filterButton_->width() - 4, filterButton_->height() - 4));
    // filterButton_->setFixedSize(18, 18);

    dependenciesList_ = new QListWidget();

    topLayout->addWidget(searchBar_);
    topLayout->addWidget(filterButton_);
    layout->addLayout(topLayout);
    layout->addWidget(dependenciesList_);

    setProperty("class", "DependenciesTree");
    searchBar_->setProperty("class", "SearchBar");
}
