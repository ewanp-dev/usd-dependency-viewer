#include "Updated.h"

RecursiveTableWidget::RecursiveTableWidget(QWidget* parent)
{
    mainLayout_ = new QVBoxLayout(this);
    
    initWidget();
}

void 
RecursiveTableWidget::setActivePath(NodePath nodePath)
{
    nodePath_   = nodePath;
    activeNode_ = nodePath_.getLeafNode();

    QString pathString;
    for (std::shared_ptr<DependencyNode> node : nodePath_)
    {
        pathString.append(" / " + node->getFileStem());
    }
}

void
RecursiveTableWidget::initWidget()
{
    initTable();
}

void 
RecursiveTableWidget::initTable()
{
}
