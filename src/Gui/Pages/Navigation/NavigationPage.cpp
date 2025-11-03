#include "NavigationPage.h"

NavigationPage::NavigationPage(const std::vector<std::string>& dependencies, std::shared_ptr<UsdDependencyGraph> graph, QWidget* parent)
{
    table_ = new RecursiveTableWidget();

    setActiveNode(graph->getRootNode());
    nodegraph_ = new Nodegraph(dependencies);
}

void NavigationPage::setActiveNode(std::shared_ptr<DependencyNode> node)
{
    activeNode_ = node;
    std::vector<std::shared_ptr<DependencyNode>> dependencyNodes = node->getChildNodes();
    table_->setActivePath(NodePath(node));
}
