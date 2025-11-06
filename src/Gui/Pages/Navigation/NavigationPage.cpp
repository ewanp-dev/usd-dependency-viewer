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

    rootNode_ = graph->getRootNode();
    setActiveNode(rootNode_);

    nodegraph_ = new Nodegraph(dependencies);
    nodegraph_->setDependencyGraph(graph);
    std::cout << "THE ROOT IS: " << graph->getRootNode()->getFilePath() << '\n';

    stackedWidget_->addWidget(nodegraph_);
    mainSplitter_->addWidget(table_);
    mainSplitter_->addWidget(stackedWidget_);
    mainLayout_->addWidget(header_);
    mainLayout_->addWidget(mainSplitter_);

    connect(table_, &RecursiveTableWidget::cellDoubleClicked, this, &NavigationPage::onTableCellDoubleClicked);
    connect(table_, &RecursiveTableWidget::navUpButtonClicked, this, &NavigationPage::onTableNavUpButtonClicked);
}

void NavigationPage::setActiveNode(std::shared_ptr<DependencyNode> node)
{
    activeNode_ = node;
    std::vector<std::shared_ptr<DependencyNode>> dependencyNodes = node->getChildNodes();
    table_->setActivePath(NodePath(node));
}

void NavigationPage::onTableCellDoubleClicked(std::shared_ptr<DependencyNode> node)
{
    nodegraph_->setActiveNode(node);
}

void NavigationPage::onTableNavUpButtonClicked(std::shared_ptr<DependencyNode> node)
{
    if (node->getFilePath() == rootNode_->getFilePath())
    {
        std::cout << "THESE ARE THE SAME" << '\n';
    }
    nodegraph_->setActiveNode(node);
}
