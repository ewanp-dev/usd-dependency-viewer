#include "RecursiveTableWidget.h"
#include <QHeaderView>
#include <qboxlayout.h>
#include <QLabel>
#include <QObject>
#include <QTimer>
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
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    mainLayout_ = new QVBoxLayout(this);
    tableHeader_ = new TableHeader();

    mainLayout_->addWidget(tableHeader_);

    initTable();


    connect(tableHeader_->getNavigationButton(), &dvWidgets::AbstractButton::clicked, this, &RecursiveTableWidget::onNavUpButtonClicked);
}


const NodePath RecursiveTableWidget::getActivePath() const
{
    return nodePath_;
}

void RecursiveTableWidget::setActivePath(NodePath nodePath)
{
    // TODO:
    //  - Refactor this into multiple functions so it's more readable

    nodePath_   = nodePath;
    activeNode_ = nodePath.getLeafNode();
    Q_EMIT navUpButtonClicked(activeNode_);

    QLineEdit* dependencyPathWidget = tableHeader_->dependencyPathWidget();
    QString pathString;

    for (std::shared_ptr<DependencyNode> node : nodePath_)
    {
        pathString.append(" / " + node->getFileStem());
    }

    dependencyPathWidget->setText(pathString);

    // NOTE: This is removing the header labels which we don't want happening
    // model_->clear();

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

    table_->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    table_->horizontalHeader()->setStretchLastSection(true);
    table_->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);

    QTimer::singleShot(0, table_, [this] {
        int cols = model_->columnCount();
        int total = table_->viewport()->width();
        int each = total / cols;

        for (int i = 0; i < cols; i++)
        {
            table_->horizontalHeader()->resizeSection(i, each);
        }
    });

    table_->verticalHeader()->setVisible(false);
}

void RecursiveTableWidget::initTable()
{
    table_ = new AbstractTable();
    table_->setStyleSheet(
        "border-top-left-radius: 4px;"
        "border-top-right-radius: 4px;"
    );

    // NOTE: Make this more dynamic incase we want to add more headers in the future
    columns_ = QStringList({
        "FILE NAME",
        "FILE PATH",
        "CHILDREN",
        "FILE SIZE",
        "DATE MODIFIED"
    });

    model_ = table_->getModel();
    model_->setColumnCount(5);
    model_->setHorizontalHeaderLabels(columns_);

    connect(table_, &QTableWidget::doubleClicked, this, &RecursiveTableWidget::onCellDoubleClicked);

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
