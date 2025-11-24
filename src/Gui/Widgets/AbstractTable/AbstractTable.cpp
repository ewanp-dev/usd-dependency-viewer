#include "AbstractTable.h"

#include <QStyledItemDelegate>

struct NoFocusDelegate : QStyledItemDelegate {

    // NOTE:
    // 
    // Very hacky workaround to removing the borders around
    // the selected cell in the table, will try to look for 
    // a better solution later

    using QStyledItemDelegate::QStyledItemDelegate;

    void paint(QPainter* p, const QStyleOptionViewItem& opt,
               const QModelIndex& idx) const override
    {
        QStyleOptionViewItem o(opt);
        o.state &= ~QStyle::State_HasFocus;   
        QStyledItemDelegate::paint(p, o, idx);
    }
};

AbstractTable::AbstractTable(QWidget* parent)
{
    model_ = new QStandardItemModel(this);

    setModel(model_);
    // setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    setShowGrid(false);
    setItemDelegate(new NoFocusDelegate(this));
}

QStandardItemModel*
AbstractTable::getModel()
{
    return model_;
}
