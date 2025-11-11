#pragma once

#include <QWidget>
#include <QLineEdit>
#include <QListWidget>
#include <Gui/Widgets/AbstractButton.h>

class DependenciesTreeWidget : public QWidget
{
    public:
        DependenciesTreeWidget(QWidget *parent = nullptr);
    private:
        QLineEdit* searchBar_;
        dvWidgets::AbstractButton* filterButton_;
        QListWidget* dependenciesList_;
};
