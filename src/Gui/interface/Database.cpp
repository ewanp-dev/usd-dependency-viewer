#include "Database.h"
#include "Core/DependencyNode.h"
#include "Globals.h"
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSizePolicy>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <vector>

DatabasePage::DatabasePage (const std::vector<std::string> &dependencies, QWidget* parent)
{
    mainLayout_ = new QVBoxLayout(this);
    mainLayout_->setContentsMargins(10, 10, 10, 10);

    initHeader();
    initTable();

}

void DatabasePage::initHeader()
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

void DatabasePage::initTable()
{
    table_ = new QTableWidget(); 
    table_->resizeRowsToContents();
    table_->verticalHeader()->setVisible(false);
    // table_->setRowCount(static_cast<int>(itemDependencies_.size()));
    table_->setColumnCount(5);
    table_->setColumnWidth(0, 400);
    table_->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    table_->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    table_->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // NOTE: We might want to add some more columns later on down the line
    // might be worth converting this to its own QStringList as a variable
    table_->setHorizontalHeaderLabels({ "File Name", "File Path", "File Size", "Extension", "Date Modified" });
    table_->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::Stretch);

    // TODO: Replace TableWidgetItems with correct options after USD Implementation
    // TODO: Look into making this more memory/speed efficient
    // TODO: Convert the font to a global font so we can use across the interface

    // for (size_t i = 0; i < itemDependencies_.size(); i++) {
    //     QTableWidgetItem *nameItem =  new QTableWidgetItem(itemDependencies_[i].c_str());
    //     QTableWidgetItem *pathItem = new QTableWidgetItem(itemDependencies_[i].c_str());
    //     QTableWidgetItem *fileSizeItem = new QTableWidgetItem(QString::number(static_cast<qulonglong>(i)));
    //     QTableWidgetItem *extensionItem = new QTableWidgetItem(QString::number(static_cast<qulonglong>(i)));
    //     QTableWidgetItem *dateModifiedItem = new QTableWidgetItem(QString::number(static_cast<qulonglong>(i)));
    //
    //     nameItem->setForeground(QBrush(QColor(210, 186, 146)));
    //     nameItem->setFont(itemFont);
    //
    //     table_->setItem(i, 0, nameItem);
    //     table_->setItem(i, 1, pathItem);
    //     table_->setItem(i, 2, fileSizeItem);
    //     table_->setItem(i, 3, extensionItem);
    //     table_->setItem(i, 4, dateModifiedItem);
    // }

    mainLayout_->addWidget(table_);
}

void DatabasePage::setDependencyGraph(UsdDependencyGraph* graph)
{
    setActiveNode(graph->getRootNode());
}

void DatabasePage::setActiveNode(DependencyNode* node)
{
    size_t numDependencies = node->getNumChildren();
    std::vector<DependencyNode*> dependencyNodes = node->getChildNodes();
    resultsList_->setText(QString::number(static_cast<qulonglong>(numDependencies)) + " Results");

    QFont itemFont = QFont("Sans Serif", 10);
    itemFont.setUnderline(true);

    table_->setRowCount(static_cast<int>(numDependencies));
    for (size_t i = 0; i < numDependencies; i++) {
        DependencyNode* dependencyNode = dependencyNodes[i];
        QTableWidgetItem *nameItem =  new QTableWidgetItem(dependencyNode->getFileName().c_str());
        QTableWidgetItem *pathItem = new QTableWidgetItem(dependencyNode->getFilePath().c_str());
        QTableWidgetItem *fileSizeItem = new QTableWidgetItem(QString::number(static_cast<qulonglong>(i)));
        QTableWidgetItem *extensionItem = new QTableWidgetItem(QString::number(static_cast<qulonglong>(i)));
        QTableWidgetItem *dateModifiedItem = new QTableWidgetItem(QString::number(static_cast<qulonglong>(i)));

        nameItem->setForeground(QBrush(QColor(210, 186, 146)));
        nameItem->setFont(itemFont);

        table_->setItem(i, 0, nameItem);
        table_->setItem(i, 1, pathItem);
        table_->setItem(i, 2, fileSizeItem);
        table_->setItem(i, 3, extensionItem);
        table_->setItem(i, 4, dateModifiedItem);
    }
}


void DatabasePage::showDropdown_(AbstractButton *button, QWidget *dropdown, int shift) {
    QPointF pos = button->mapToGlobal(button->rect().bottomLeft());
    if (shift > 0) {
        int posX = pos.x() - shift;
        pos.setX(posX);
    }

    dropdown->move(pos.x(), pos.y());
    dropdown->show();
}
