#include "RecursiveViewPage.h"
#include "Core/DependencyNode.h"
#include "Core/NodePath.h"
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

    size_t numDependencies = activeNode_->getNumChildren();
    resultsList_->setText(QString::number(static_cast<qulonglong>(numDependencies)) + " Results");

    table_->setActivePath(NodePath(node));
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

