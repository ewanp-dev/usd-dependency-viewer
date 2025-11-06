#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <memory>

#include <Gui/Pages/Navigation/Frameworks/Nodegraph/ForceDirectedGraph.h>
#include <Core/DependencyNode.h>
#include <Core/UsdDependencyGraph.h>

class Nodegraph : public QWidget
{
    public:
        Nodegraph(const std::vector<std::string>& dependencies, QWidget* parent = nullptr);
        void setDependencyGraph(std::shared_ptr<UsdDependencyGraph> graph);
        void setActiveNode(std::shared_ptr<DependencyNode> node);
        void clear();

    private:
        void initGraph();

        fdg::ForceDirectedGraph* graph_;
        std::shared_ptr<DependencyNode> activeNode_;
        std::shared_ptr<DependencyNode> rootNode_;

        QVBoxLayout* mainLayout_;

};
