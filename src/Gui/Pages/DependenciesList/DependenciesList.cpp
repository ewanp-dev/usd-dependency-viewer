
#include "DependenciesList.h"

#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <Gui/Widgets/AbstractTable.h>

DependenciesListPage::DependenciesListPage(std::vector<std::string> dependencies, QWidget* parent)
{
    mainLayout_ = new QVBoxLayout(this);

    pageLabel_ = new QLabel("Dependencies List Page");

    setTable(dependencies); 
}

void DependenciesListPage::setTable(std::vector<std::string> items)
{
    AbstractTable* table = new AbstractTable();
    table->verticalHeader()->setVisible(false);
    QStandardItemModel* model_ = table->getModel();
    model_->setColumnCount(1);
    model_->setRowCount(static_cast<int>(items.size()));
    model_->setHorizontalHeaderLabels({ "FILE PATH" });

    for (int i = 0; i < static_cast<int>(items.size()); i++)
    {
        auto* item = new QStandardItem(QString::fromStdString(items[i]));    
        model_->setItem(i, 0, item);
    }

    table->horizontalHeader()->setStretchLastSection(true);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    mainLayout_->addWidget(table);

}
