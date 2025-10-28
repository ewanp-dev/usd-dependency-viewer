#pragma once

#include "Gui/interface/AbstractButton.h"
#include "Core/DependencyNode.h"
#include "Core/UsdDependencyGraph.h"
#include "Gui/interface/widgets/dropdown/Results.h"
#include "Gui/interface/widgets/dropdown/Sort.h"
#include "Gui/interface/widgets/dropdown/Properties.h"
#include "Gui/pages/ForceDirectedGraphPage/ForceDirectedGraphPage.h"
#include "RecursiveTableWidget.h"
#include <vector>
#include <QHBoxLayout>
#include <QSplitter>

class RecursiveViewPage : public QWidget
{
    public:
        RecursiveViewPage(const std::vector<std::string> &dependencies, QWidget* parent = nullptr);
        void setActiveNode(std::shared_ptr<DependencyNode> node);
        void setDependencyGraph(std::shared_ptr<UsdDependencyGraph> graph);
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
        QSplitter* mainSplitter_;
        std::shared_ptr<DependencyNode> activeNode_;

        void hideColumn_();
        void showDropdown_(AbstractButton *button, QWidget *dropdown, int shift = 0);
        void switchSortType();
        AbstractButton* resultsList_;
        AbstractButton* sort_;
        AbstractButton* properties_;
        RecursiveTableWidget* table_;
        void onCellDoubleClicked(int row, int column);
        ResultsDropdownWidget* resultsDropdown_;
        SortDropdownWidget* sortDropdown_;
        PropertiesDropdownWidget* propertiesDropdown_;
        ForceDirectedGraphPage* nodegraphPage_;
        // ForceDirectedGraphPage* nodegraphPage_;
};
