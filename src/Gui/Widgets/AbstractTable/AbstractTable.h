#pragma once

#include <QTableView>
#include <QStandardItemModel>

// NOTE:
// 
// This is just a small wrapper around the QTableView to simplify
// some boilerplate code. This class can be expanded upon in the future
// if need be.
//
// I also just used a StandardItemModel as our datasets probably won't be
// big enough to justify an AbstractItemModel

class AbstractTable : public QTableView
{
    public:
        AbstractTable(QWidget* parent = nullptr);

        QStandardItemModel* getModel();

    private:
        QStandardItemModel* model_;
};
