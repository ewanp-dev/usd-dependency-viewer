#include "NavigationPage.h"

#include <iostream>

// TODO:
//  - Remove outline from the nodegraph
//  - Update stylesheet of the main QSplitter class


NavigationPage::NavigationPage(const std::vector<std::string>& dependencies, std::shared_ptr<UsdDependencyGraph> graph, QWidget* parent)
    : dependencies_(dependencies), graph_(graph)
{
    setContentsMargins(0, 0, 0, 0);
    initWidgets();
}

void NavigationPage::setActiveNode(NodePath nodePath)
{
    nodePath_ = nodePath;
    activeNode_ = nodePath.getLeafNode();

    nodegraph_->setActiveNode(activeNode_);

    std::vector<std::shared_ptr<DependencyNode>> dependencyNodes = activeNode_->getChildNodes();

    QLineEdit* dependencyPathWidget = header_->dependencyPathWidget();
    QString pathString;

    for (std::shared_ptr<DependencyNode> node : nodePath_)
    {
        pathString.append(" / " + node->getFileStem());
    }

    dependencyPathWidget->setText(pathString);

    size_t numDependencies = activeNode_->getNumChildren();
    
    for (size_t i = 0; i < numDependencies; i++)
    {
        std::shared_ptr<DependencyNode> dependencyNode = dependencyNodes[i];
        itemArea_->addItem(dependencyNode);
    }
}

const NodePath NavigationPage::getActivePath() const
{
    return nodePath_;
}

void NavigationPage::onItemWidgetDoubleClicked(const std::string& filePath)
{
    itemArea_->clearItems();

    std::vector<std::shared_ptr<DependencyNode>> childNodes = activeNode_->getChildNodes();
    for(auto node : childNodes)
    {
        if(node->getFilePath() == filePath)
        {
            if(node->getNumChildren()==0)
            {
                break;
            }

            setActiveNode(getActivePath().appendNode(node));
            break;
        }
    }

    for (ItemWidget* item : itemArea_->getItems())
    {
        connect(item, &ItemWidget::itemDoubleClicked, this, &NavigationPage::onItemWidgetDoubleClicked);
    }
}

void NavigationPage::onNavUpButtonClicked(std::shared_ptr<DependencyNode> node)
{

    const NodePath& nodePath = getActivePath();

    // guard against emptying path
    if (nodePath.getLeafNode() == nodePath.getRootNode()) return;

    itemArea_->clearItems();
    setActiveNode(nodePath.popNode());

    for (ItemWidget* item : itemArea_->getItems())
    {
        connect(item, &ItemWidget::itemDoubleClicked, this, &NavigationPage::onItemWidgetDoubleClicked);
    }
}

void NavigationPage::initWidgets()
{
    // TODO:
    //  - Move signals to somewhere more appropriate

    mainLayout_ = new QVBoxLayout(this);

    mainSplitter_ = new QSplitter();

    header_ = new TableHeader();
    itemBackgroundWidget_ = new ItemBackgroundWidget();
    itemArea_ = itemBackgroundWidget_->getListWidget();

    stackedWidget_ = new NavigationStackedWidget(dependencies_);
    nodegraph_ = stackedWidget_->nodegraph();

    rootNode_ = graph_->getRootNode();
    setActiveNode(rootNode_);
    nodegraph_->setDependencyGraph(graph_);

    for (ItemWidget* item : itemArea_->getItems())
    {
        connect(item, &ItemWidget::itemDoubleClicked, this, &NavigationPage::onItemWidgetDoubleClicked);
    }
    connect(itemBackgroundWidget_->getNavigationButton(), &dvWidgets::AbstractButton::clicked, this, [this] () {
        onNavUpButtonClicked(activeNode_);
    });

    mainSplitter_->addWidget(itemBackgroundWidget_);
    mainSplitter_->addWidget(stackedWidget_);
    mainSplitter_->setSizes({200, 200});
    mainSplitter_->setContentsMargins(0, 0, 0, 0);

    mainLayout_->addWidget(header_);
    mainLayout_->addWidget(mainSplitter_);
}



