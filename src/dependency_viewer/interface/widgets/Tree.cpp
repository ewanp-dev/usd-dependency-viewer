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
    searchBar_->setPlaceholderText("> Search...");
    searchBar_->setFixedHeight(25);

    filterButton_ = new AbstractButton();
    filterButton_->setIconFromImage(DV_ELEMENTS_DIRECTORY + "filter.png");
    filterButton_->setIconSize(QSize(filterButton_->width() - 4, filterButton_->height() - 4));
    // filterButton_->setFixedSize(18, 18);

    dependenciesList_ = new QListWidget();

    topLayout->addWidget(searchBar_);
    topLayout->addWidget(filterButton_);
    layout->addLayout(topLayout);
    layout->addWidget(dependenciesList_);

    searchBar_->setStyleSheet(R"(
        QLineEdit {
            background-color: rgb(60, 60, 60);
            color: rgb(210, 210, 210);
            padding-left: 6px;
            padding-right: 6px;
            border-radius: 0px;
        }
    )");

    dependenciesList_->setStyleSheet(R"(
        QListWidget {
            background: transparent;
            border: none;
        }
    )");

    setStyleSheet(R"(
        QWidget {
            background-color: rgb(20, 20, 20);
        }
    )");
}
