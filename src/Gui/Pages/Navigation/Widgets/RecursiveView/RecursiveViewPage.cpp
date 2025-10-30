#include "RecursiveViewPage.h"
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSizePolicy>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <qsplitter.h>
#include <qstackedwidget.h>
#include <vector>
#include <QLabel>
#include <iostream>

#include <Core/DependencyNode.h> 
#include <Core/NodePath.h>

RecursiveViewPage::RecursiveViewPage (const std::vector<std::string> &dependencies, QWidget* parent)
{
    initTable();
}

void RecursiveViewPage::initTable()
{
    table_ = new RecursiveTableWidget(); 

    mainSplitter_->addWidget(table_);
}

void RecursiveViewPage::setDependencyGraph(std::shared_ptr<UsdDependencyGraph> graph)
{
    std::cout << "Setting dependency graph" << '\n';
    setActiveNode(graph->getRootNode()); 
}

void RecursiveViewPage::setActiveNode(std::shared_ptr<DependencyNode> node)
{
    activeNode_ = node;

    // table_->clearContents();
    // connect(table_, &QTableWidget::cellDoubleClicked, this, &RecursiveViewPage::onCellDoubleClicked);

    size_t numDependencies = node->getNumChildren();
    std::vector<std::shared_ptr<DependencyNode>> dependencyNodes = node->getChildNodes();

    table_->setActivePath(NodePath(node));
}
