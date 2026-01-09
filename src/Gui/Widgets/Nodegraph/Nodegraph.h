#pragma once

#include <QWidget>
#include <QVBoxLayout>

#include <memory>

#include <Core/Nodegraph/ForceDirectedGraph.h>
#include <Core/DependencyNode.h>
#include <Core/UsdDependencyGraph.h>

#include <Gui/Widgets/AbstractWidgets/AbstractButton.h>

class Nodegraph : public QWidget
{
    public:
        Nodegraph(const std::vector<std::string>& dependencies, QWidget* parent = nullptr);
        void setDependencyGraph(std::shared_ptr<UsdDependencyGraph> graph);
        void setActiveNode(std::shared_ptr<DependencyNode> node);
        void setSelectedNodeItem(const std::string& fileName);
        std::vector<fdg::Node*> getAllNodes();
        void clear();

    private:
        void initGraph();

        fdg::ForceDirectedGraph* graph_;

        std::shared_ptr<DependencyNode> activeNode_;
        std::shared_ptr<DependencyNode> rootNode_;


        QVBoxLayout* mainLayout_;
};
