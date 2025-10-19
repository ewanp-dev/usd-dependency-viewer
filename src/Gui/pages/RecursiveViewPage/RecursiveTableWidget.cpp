#include "RecursiveTableWidget.h"
#include <QHeaderView>

RecursiveTableWidget::RecursiveTableWidget()
{
    this->resizeRowsToContents();
    this->verticalHeader()->setVisible(false);
    // this->setRowCount(static_cast<int>(itemDependencies_.size()));
    this->setColumnCount(5);
    this->setColumnWidth(0, 400);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    this->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // NOTE: We might want to add some more columns later on down the line
    // might be worth converting this to its own QStringList as a variable
    this->setHorizontalHeaderLabels({ "File Name", "File Path", "Children", "File Size", "Date Modified" });
    this->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::Stretch);
}
