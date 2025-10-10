#pragma once

#include "AbstractButton.h"
#include "widgets/dropdown/Results.h"
#include "widgets/dropdown/Sort.h"
#include "widgets/dropdown/Properties.h"
#include <QTableWidget>
#include <vector>

class DatabasePage : public QWidget
{
    public:
        DatabasePage(const std::vector<std::string> &dependencies, QWidget* parent = nullptr);
    private:
        void hideColumn_();
        void showDropdown_(AbstractButton *button, QWidget *dropdown, int shift = 0);
        void switchSortType();
        AbstractButton* resultsList_;
        AbstractButton* sort_;
        AbstractButton* properties_;
        QTableWidget* table_;
        std::vector<std::string> itemDependencies_;
        ResultsDropdownWidget* resultsDropdown_;
        SortDropdownWidget* sortDropdown_;
        PropertiesDropdownWidget* propertiesDropdown_;
};
