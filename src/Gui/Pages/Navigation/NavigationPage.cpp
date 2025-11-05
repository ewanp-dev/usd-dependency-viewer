#include "NavigationPage.h"

// TODO
// Add in dependency graph to the nodegraph
// Add in table signals and slots


NavigationPage::NavigationPage(const std::vector<std::string>& dependencies, std::shared_ptr<UsdDependencyGraph> graph, QWidget* parent)
{
    mainLayout_ = new QVBoxLayout(this);
    mainLayout_->setContentsMargins(10, 10, 10, 10);
    mainSplitter_ = new QSplitter();
    stackedWidget_ = new QStackedWidget();
    table_ = new RecursiveTableWidget();
    header_ = new NavigationHeader();

    setActiveNode(graph->getRootNode());

    nodegraph_ = new Nodegraph(dependencies);
    nodegraph_->setDependencyGraph(graph);

    stackedWidget_->addWidget(nodegraph_);
    mainSplitter_->addWidget(table_);
    mainSplitter_->addWidget(stackedWidget_);
    mainLayout_->addWidget(header_);
    mainLayout_->addWidget(mainSplitter_);
}

void NavigationPage::setActiveNode(std::shared_ptr<DependencyNode> node)
{
    activeNode_ = node;
    std::vector<std::shared_ptr<DependencyNode>> dependencyNodes = node->getChildNodes();
    table_->setActivePath(NodePath(node));
}
