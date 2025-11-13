#include "RecursiveTableWidget.h"
#include <QHeaderView>
#include <qboxlayout.h>
#include <QLabel>
#include <iostream>
#include <QObject>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QToolTip>
#include <qtablewidget.h>
#include <qtextedit.h>
#include <QResizeEvent>
#include <Gui/Widgets/AbstractButton.h>

RecursiveTableWidget::RecursiveTableWidget()
{
    setContentsMargins(0,0,0,0);

    mainLayout_ = new QVBoxLayout(this);
    tableHeader_ = new TableHeader();

    mainLayout_->addWidget(tableHeader_);

    initTable();
}


const NodePath RecursiveTableWidget::getActivePath() const
{
    return nodePath_;
}

void RecursiveTableWidget::setActivePath(NodePath nodePath)
{
    nodePath_ = nodePath;
    activeNode_ = nodePath.getLeafNode();
    QLineEdit* dependencyPathWidget = tableHeader_->dependencyPathWidget();

    Q_EMIT navUpButtonClicked(activeNode_);

    QString pathString;

    for (std::shared_ptr<DependencyNode> node : nodePath_)
    {
        pathString.append(" / "+node->getFileStem());
    }

    dependencyPathWidget->setText(pathString);

    model_->clear();

    size_t numDependencies = activeNode_->getNumChildren();
    std::vector<std::shared_ptr<DependencyNode>> dependencyNodes = activeNode_->getChildNodes();

    model_->setRowCount(static_cast<int>(numDependencies));

    for (size_t i = 0; i < numDependencies; i++) 
    {
        std::shared_ptr<DependencyNode> dependencyNode = dependencyNodes[i];

        // File Name Column
        QString fileName = dependencyNode->getFileName().c_str();
        QStandardItem* nameItem =  new QStandardItem(fileName);
        nameItem->setToolTip(fileName);
        nameItem->setEditable(false);
        nameItem->setForeground(QBrush(QColor(210, 186, 146)));

        // File Path Column
        QString filePath = dependencyNode->getFilePath().c_str();
        QStandardItem* pathItem = new QStandardItem(filePath);
        pathItem->setToolTip(filePath);
        pathItem->setEditable(false);

        // File Size Column
        QStandardItem* fileSizeItem = new QStandardItem(QString::number(static_cast<qulonglong>(i)));
        fileSizeItem->setEditable(false);

        // Children Number Column
        QStandardItem* numChildrenItem = new QStandardItem(QString::number(dependencyNode->getNumChildren()));
        numChildrenItem->setEditable(false);

        // Date Modified Column
        QStandardItem* dateModifiedItem = new QStandardItem(QString::number(static_cast<qulonglong>(i)));
        dateModifiedItem->setEditable(false);

        model_->setItem(i, 0, nameItem);
        model_->setItem(i, 1, pathItem);
        model_->setItem(i, 2, numChildrenItem);
        model_->setItem(i, 3, fileSizeItem);
        model_->setItem(i, 4, dateModifiedItem);
    }

    table_->onHeaderResized();
}

void RecursiveTableWidget::initTable()
{
    table_ = new dvWidgets::AbstractTable();
    model_ = new QStandardItemModel();

    table_->setModel(model_);
    model_->setColumnCount(5);

    // NOTE: We might want to add some more columns later on down the line
    // might be worth converting table_ to its own QStringList as a variable
    table_->setHorizontalHeaderLabels({ "File Name", "File Path", "Children", "File Size", "Date Modified" });

    connect(table_->getView(), &QTableWidget::doubleClicked, this, &RecursiveTableWidget::onCellDoubleClicked);

    mainLayout_->addWidget(table_);
}

void RecursiveTableWidget::onNavUpButtonClicked()
{
    const NodePath& nodePath = getActivePath();

    // guard against emptying path
    if (nodePath.getLeafNode() == nodePath.getRootNode()) return;

    setActivePath(nodePath.popNode());
}

void RecursiveTableWidget::onCellDoubleClicked(const QModelIndex& index)
{
    // NOTE: not the best way to get the graph nod3 but it's fine.

    int row = index.row();
    int column = index.column();

    auto tableItem = model_->item(row, 1);
    if(!tableItem)
    {
        return;
    }
    std::string filePath = tableItem->text().toStdString();

    std::vector<std::shared_ptr<DependencyNode>> childNodes = activeNode_->getChildNodes();
    for(auto node : childNodes)
    {
        if(node->getFilePath() == filePath)
        {
            if(node->getNumChildren()==0)
            {
                break;
            }

            setActivePath(getActivePath().appendNode(node));
            Q_EMIT cellDoubleClicked(node);
            break;
        }
    }
}
