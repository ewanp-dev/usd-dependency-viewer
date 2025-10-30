#pragma once

#include "RecursiveTableWidget.h"

#include <vector>
#include <QHBoxLayout>
#include <QSplitter>

#include <Core/DependencyNode.h>
#include <Core/UsdDependencyGraph.h>

class RecursiveViewPage : public QWidget
{
    public:
        RecursiveViewPage(const std::vector<std::string> &dependencies, QWidget* parent = nullptr);
        void setActiveNode(std::shared_ptr<DependencyNode> node);
        void setDependencyGraph(std::shared_ptr<UsdDependencyGraph> graph);
    private:
        void initTable();

        QVBoxLayout* mainLayout_;
        QSplitter* mainSplitter_;
        std::shared_ptr<DependencyNode> activeNode_;

        void hideColumn_();
        void switchSortType();
        void onCellDoubleClicked(int row, int column);
        RecursiveTableWidget* table_;
};
