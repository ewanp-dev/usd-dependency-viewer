#pragma once

#include "AbstractButton.h"
#include <QTableWidget>
#include <vector>

class DatabasePage : public QWidget
{
    public:
        DatabasePage(const std::vector<std::string> &dependencies, QWidget* parent = nullptr);
    private:
        void hideColumn_();
        void showDropdown_();
        void switchSortType();
        AbstractButton* viewSwitcher_;
        AbstractButton* resultsList_;
        AbstractButton* sort_;
        AbstractButton* properties_;
        QTableWidget* table_;
        std::vector<std::string> itemDependencies_;
};
