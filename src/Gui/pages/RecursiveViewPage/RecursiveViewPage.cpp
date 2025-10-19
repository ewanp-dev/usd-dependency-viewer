#include "RecursiveViewPage.h"
#include "Core/DependencyNode.h"
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

RecursiveViewPage::RecursiveViewPage (const std::vector<std::string> &dependencies, QWidget* parent)
{
    mainLayout_ = new QVBoxLayout(this);
    mainLayout_->setContentsMargins(10, 10, 10, 10);

    mainSplitter_ = new QSplitter();

    mainLayout_->addWidget(mainSplitter_);

    initHeader();
    initTable();

    QStackedWidget* stackedWidget = new QStackedWidget();

    mainSplitter_->addWidget(stackedWidget);
}

void RecursiveViewPage::initHeader()
{
    QHBoxLayout* layoutHeader = new QHBoxLayout();
    layoutHeader->setContentsMargins(10, 5, 10, 5);

    resultsList_ = new AbstractButton();
    resultsList_->setFixedWidth(100);
    resultsList_->setSizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);

    sort_ = new AbstractButton();
    sort_->setSizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
    sort_->setIconFromImage(":icons/filter.png");

    properties_ = new AbstractButton();
    properties_->setSizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
    properties_->setIconFromImage(":icons/properties.png");

    resultsDropdown_ = new ResultsDropdownWidget();
    sortDropdown_ = new SortDropdownWidget();
    propertiesDropdown_ = new PropertiesDropdownWidget();

    connect(resultsList_, &AbstractButton::clicked, this, [this]() {
        showDropdown_(resultsList_, resultsDropdown_);
    });

    connect(sort_, &AbstractButton::clicked, this, [this]() {
        showDropdown_(sort_, sortDropdown_, 200);
    });

    connect(properties_, &AbstractButton::clicked, this, [this]() {
        showDropdown_(properties_, propertiesDropdown_, 100);
    });

    layoutHeader->addWidget(resultsList_);
    layoutHeader->addStretch(1);
    layoutHeader->addWidget(sort_);
    layoutHeader->addWidget(properties_);

    mainLayout_->addLayout(layoutHeader);
}

void RecursiveViewPage::initTable()
{
    table_ = new RecursiveTableWidget(); 

    mainSplitter_->addWidget(table_);
}

void RecursiveViewPage::setDependencyGraph(UsdDependencyGraph* graph)
{
    setActiveNode(graph->getRootNode());
}

void RecursiveViewPage::setActiveNode(std::shared_ptr<DependencyNode> node)
{
    activeNode_ = node;

    table_->clearContents();
    connect(table_, &QTableWidget::cellDoubleClicked, this, &RecursiveViewPage::onCellDoubleClicked);

    size_t numDependencies = node->getNumChildren();
    std::cout << "num children: " << numDependencies << "\n";
    std::vector<std::shared_ptr<DependencyNode>> dependencyNodes = node->getChildNodes();
    resultsList_->setText(QString::number(static_cast<qulonglong>(numDependencies)) + " Results");

    // TODO: Convert the font to a global font so we can use across the interface
    QFont itemFont = QFont("Sans Serif", 10);
    itemFont.setUnderline(true);

    table_->setRowCount(static_cast<int>(numDependencies));
    for (size_t i = 0; i < numDependencies; i++) {
        std::shared_ptr<DependencyNode> dependencyNode = dependencyNodes[i];
        QTableWidgetItem *nameItem =  new QTableWidgetItem(dependencyNode->getFileName().c_str());
        QTableWidgetItem *pathItem = new QTableWidgetItem(dependencyNode->getFilePath().c_str());
        QTableWidgetItem *fileSizeItem = new QTableWidgetItem(QString::number(static_cast<qulonglong>(i)));
        QTableWidgetItem *numChildrenItem = new QTableWidgetItem(QString::number(dependencyNode->getNumChildren()));
        QTableWidgetItem *dateModifiedItem = new QTableWidgetItem(QString::number(static_cast<qulonglong>(i)));

        nameItem->setForeground(QBrush(QColor(210, 186, 146)));
        nameItem->setFont(itemFont);

        table_->setItem(i, 0, nameItem);
        table_->setItem(i, 1, pathItem);
        table_->setItem(i, 2, numChildrenItem);
        table_->setItem(i, 3, fileSizeItem);
        table_->setItem(i, 4, dateModifiedItem);
    }
}


void RecursiveViewPage::showDropdown_(AbstractButton *button, QWidget *dropdown, int shift) {
    QPointF pos = button->mapToGlobal(button->rect().bottomLeft());
    if (shift > 0) {
        int posX = pos.x() - shift;
        pos.setX(posX);
    }

    dropdown->move(pos.x(), pos.y());
    dropdown->show();
}

void RecursiveViewPage::onCellDoubleClicked(int row, int column)
{
    // NOTE: not the best way to get the graph nod3 but it's fine.

    std::cout << "double clicked\n";
    auto tableItem = table_->item(row, 1);
    if(!tableItem)
    {
        std::cout << "table item doesn't exist\n";
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
                std::cout << "Node has no children\n";
                break;
            }
            std::cout << "setting active node\n";
            std::cout << "path: " << filePath << "\n";
            setActiveNode(node);
            break;
        }
    }
}
