#include "Nodegraph.h"

#include <QTimer>

#include <memory>

Nodegraph::Nodegraph(const std::vector<std::string>& dependencies, QWidget* parent)
    : QWidget(parent), graph_(new fdg::ForceDirectedGraph(this))
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setContentsMargins(0, 0, 0, 0);

    QWidget* container = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(this);
    mainLayout_ = new QVBoxLayout(container);

    layout->addWidget(container);
    layout->setContentsMargins(0, 8, 8, 0);
    container->setAttribute(Qt::WidgetAttribute::WA_StyledBackground, true);
    container->setProperty("class", "standardWidget");
    container->setStyleSheet(
        "border-top-left-radius: 4px;"
        "border-top-right-radius: 4px;"
    );
    container->setContentsMargins(0, 0, 0, 0);

    mainLayout_->addWidget(graph_);

    QTimer::singleShot(0, graph_, &fdg::ForceDirectedGraph::initSimulation);
}

void Nodegraph::setDependencyGraph(std::shared_ptr<UsdDependencyGraph> graph)
{
    setActiveNode(graph->getRootNode());
}

void Nodegraph::setActiveNode(std::shared_ptr<DependencyNode> node)
{
    activeNode_ = node;
    initGraph();
}

std::vector<fdg::Node*> Nodegraph::getAllNodes()
{
    return graph_->nodeStore();
}

void Nodegraph::initGraph()
{
    clear();
    std::vector<std::shared_ptr<DependencyNode>> dependencyNodes = activeNode_->getChildNodes();
    fdg::Node* rootNode = graph_->addNode(activeNode_->getFileName().c_str());
    rootNode->setNodePath(activeNode_->getFilePath().c_str());
    rootNode->setPos(10.0, 20.0); // TODO: Change magic numbers

    for ( size_t i = 0; i < dependencyNodes.size(); i++ )
    {
        fdg::Node* depNode = graph_->addNode(dependencyNodes[i]->getFileName().c_str());
        depNode->setNodePath(dependencyNodes[i]->getFilePath().c_str());
        graph_->connectNodes(rootNode, depNode);
        depNode->setPos(static_cast<float>(i) * 20.0, static_cast<float>(i) * 20.0);
    }
}

void Nodegraph::clear()
{
    graph_->clearNodes();
}

void Nodegraph::setSelectedNodeItem(const std::string& fileName)
{
    graph_->setNodeAsSelected(fileName);
}
