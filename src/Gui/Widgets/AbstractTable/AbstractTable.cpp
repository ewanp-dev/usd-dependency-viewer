#include "AbstractTable.h"

AbstractTable::AbstractTable(int columnCount, const QStringList& labels, QWidget* parent)
{
    model_ = new QStandardItemModel(this);
    model_->setColumnCount(columnCount);
    model_->setHorizontalHeaderLabels(labels);

    setModel(model_);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
}

QStandardItemModel*
AbstractTable::getModel()
{
    return model_;
}
