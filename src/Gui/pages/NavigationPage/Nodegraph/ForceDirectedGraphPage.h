#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include "Gui/interface/widgets/nodegraph/ForceDirectedGraph.h"
#include <memory>

#include "Core/DependencyNode.h"
#include "Core/UsdDependencyGraph.h"

class ForceDirectedGraphPage : public QWidget
{
    public:
        ForceDirectedGraphPage(const std::vector<std::string>& dependencies, QWidget* parent = nullptr);
        void setDependencyGraph(std::shared_ptr<UsdDependencyGraph> graph);
        void setActiveNode(std::shared_ptr<DependencyNode> node);
        void clear();

    private:
        void initGraph();

        fdg::ForceDirectedGraph* graph_;
        std::shared_ptr<DependencyNode> activeNode_;

        QVBoxLayout* mainLayout_;

};
