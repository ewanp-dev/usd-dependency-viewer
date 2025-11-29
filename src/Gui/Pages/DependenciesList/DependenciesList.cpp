
#include "DependenciesList.h"

#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>

DependenciesListPage::DependenciesListPage(std::vector<std::string> dependencies, QWidget* parent)
{
    mainLayout_ = new QVBoxLayout(this);

    pageLabel_ = new QLabel("Dependencies List Page");

    setTable(dependencies); 
}

void DependenciesListPage::setTable(std::vector<std::string> items)
{
    QTableWidget* table = new QTableWidget;
    table->setColumnCount(1);
    table->setRowCount(static_cast<int>(items.size()));
    table->setHorizontalHeaderLabels({ "Value" });

    for (int i = 0; i < static_cast<int>(items.size()); i++)
    {
        auto* item = new QTableWidgetItem(QString::fromStdString(items[i]));    
        table->setItem(i, 0, item);
    }

    table->horizontalHeader()->setStretchLastSection(true);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    mainLayout_->addWidget(table);

}
