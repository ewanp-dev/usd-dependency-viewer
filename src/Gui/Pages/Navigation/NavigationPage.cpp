#include "NavigationPage.h"

// TODO:
//  - Remove outline from the nodegraph
//  - Fix the splitter style


NavigationPage::NavigationPage(const std::vector<std::string>& dependencies, std::shared_ptr<UsdDependencyGraph> graph, QWidget* parent)
    : dependencies_(dependencies), graph_(graph)
{
    initWidgets();
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
    nodegraph_->setActiveNode(node);
}

void NavigationPage::initWidgets()
{
    // TODO:
    //  - Move signals to somewhere more appropriate

    mainLayout_ = new QVBoxLayout(this);
    mainLayout_->setContentsMargins(0, 0, 0, 0);

    mainSplitter_ = new QSplitter();

    table_ = new RecursiveTableWidget();
    stackedWidget_ = new NavigationStackedWidget(dependencies_);
    nodegraph_ = stackedWidget_->nodegraph();

    rootNode_ = graph_->getRootNode();
    setActiveNode(rootNode_);

    nodegraph_->setDependencyGraph(graph_);

    mainSplitter_->addWidget(table_);
    mainSplitter_->addWidget(stackedWidget_);
    mainSplitter_->setSizes({200, 200});

    mainLayout_->addWidget(mainSplitter_);

    connect(table_, &RecursiveTableWidget::cellDoubleClicked, this, &NavigationPage::onTableCellDoubleClicked);
    connect(table_, &RecursiveTableWidget::navUpButtonClicked, this, &NavigationPage::onTableNavUpButtonClicked);
}


