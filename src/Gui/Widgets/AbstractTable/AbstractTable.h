#pragma once

#include <QTableView>
#include <QStandardItemModel>

class AbstractTable : public QTableView
{
    public:
        AbstractTable(
            int columnCount, 
            const QStringList& labels,
            QWidget* parent = nullptr
        );

        QStandardItemModel* getModel();

    private:
        QStandardItemModel* model_;
};
