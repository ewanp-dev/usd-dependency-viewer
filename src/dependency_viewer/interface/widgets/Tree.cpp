#include "Tree.h"
#include "../Globals.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

DependenciesTreeWidget::DependenciesTreeWidget(QWidget *parent) {
    setMinimumWidth(45);

    QVBoxLayout* layout = new QVBoxLayout(this);
    QHBoxLayout* topLayout = new QHBoxLayout();
    layout->setContentsMargins(15, 15, 15, 15);

    searchBar_ = new QLineEdit();
    searchBar_->setPlaceholderText("Search...");

    filterButton_ = new AbstractButton();
    filterButton_->setIconFromImage(DV_ELEMENTS_DIRECTORY + "filter.png");
    filterButton_->setFixedSize(18, 18);

    dependenciesList_ = new QListWidget();

    topLayout->addWidget(searchBar_);
    topLayout->addWidget(filterButton_);
    layout->addLayout(topLayout);
    layout->addWidget(dependenciesList_);
}
