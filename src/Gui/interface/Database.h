#pragma once

#include "AbstractButton.h"
#include "Core/DependencyNode.h"
#include "Core/DependencyEvaluation.h"
#include "widgets/dropdown/Results.h"
#include "widgets/dropdown/Sort.h"
#include "widgets/dropdown/Properties.h"
#include <QTableWidget>
#include <vector>
#include <QHBoxLayout>

class DatabasePage : public QWidget
{
    public:
        DatabasePage(const std::vector<std::string> &dependencies, QWidget* parent = nullptr);
        void setActiveNode(DependencyNode* node);
        void setDependencyGraph(UsdDependencyGraph* graph);
    private:
        /**
         * @brief Setup header view only
         */
        void initHeader();
        /**
         * @brief Setup table view only
         */
        void initTable();

        QVBoxLayout* mainLayout_;

        void hideColumn_();
        void showDropdown_(AbstractButton *button, QWidget *dropdown, int shift = 0);
        void switchSortType();
        AbstractButton* resultsList_;
        AbstractButton* sort_;
        AbstractButton* properties_;
        QTableWidget* table_;
        ResultsDropdownWidget* resultsDropdown_;
        SortDropdownWidget* sortDropdown_;
        PropertiesDropdownWidget* propertiesDropdown_;
};
