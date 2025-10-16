#pragma once

#include <QWidget>
#include <QLineEdit>
#include <QListWidget>
#include "../AbstractButton.h"


class DependenciesTreeWidget : public QWidget
{
    public:
        DependenciesTreeWidget(QWidget *parent = nullptr);
    private:
        QLineEdit* searchBar_;
        AbstractButton* filterButton_;
        QListWidget* dependenciesList_;
};
