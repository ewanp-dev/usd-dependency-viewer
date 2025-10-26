#include "./TableWidget.h"
#include <qboxlayout.h>
#include <qpushbutton.h>
#include <qsplitter.h>
#include <qtableview.h>
#include <qheaderview.h>
#include <iostream>

class SimpleModel : public QAbstractTableModel {
public:
    int rowCount(const QModelIndex & = QModelIndex()) const override { return 3; }
    int columnCount(const QModelIndex & = QModelIndex()) const override { return 3; }

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override {
        if (role == Qt::DisplayRole)
            return QString("Hello World R%1C%2").arg(index.row()).arg(index.column());
        return {};
    }
};

TableWidget::TableWidget()
{
    mainLayout_ = new QVBoxLayout();
    setLayout(mainLayout_);

    initHeader();
    initBody();
}

void TableWidget::initHeader()
{

    header_ = new QWidget();
    header_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    header_->setProperty("class", "TableHeader");
    header_->setFixedHeight(30);

    QHBoxLayout* headerLayout = new QHBoxLayout(header_);
    headerLayout->setContentsMargins(0,0,0,0);

    // QSplitter* splitter1 = new QSplitter();
    headerSplitter_ = new QSplitter();;
    // QSplitter* splitter2 = new QSplitter();
    // QSplitter* splitter3 = new QSplitter();

    // splitters_.push_back(splitter1);
    // splitters_.push_back(splitter2);
    // splitters_.push_back(splitter3);

    headerLayout->addWidget(headerSplitter_);

    QPushButton* button1 = new QPushButton("hello");
    // for(auto splitter : splitters_)
    // {
    //     splitter->setCollapsible(0, false);
    //     splitter->setCollapsible(2, false);
    //     connect(splitter, &QSplitter::splitterMoved, this, &TableWidget::onHeaderResize);
    // }

    connect(headerSplitter_, &QSplitter::splitterMoved, this, &TableWidget::onHeaderResize);

    headerSplitter_->addWidget(button1);
    // splitter1->addWidget(splitter2);
    headerSplitter_->addWidget(new QPushButton("world"));
    // splitter2->addWidget(splitter3);
    headerSplitter_->addWidget(new QPushButton("foo"));
    // splitter3->addWidget(new QPushButton("bar"));

    for(size_t i=0; i<headerSplitter_->count(); ++i)
    {
        headerSplitter_->setCollapsible(i, false);
    }

    mainLayout_->addWidget(header_);
}

void TableWidget::onHeaderResize(int pos, int index)
{
    for(size_t i=0; i<headerSplitter_->count(); ++i)
    {
        int width = headerSplitter_->sizes()[i];
        view_->setColumnWidth(i, width);
    }
}

void TableWidget::initBody()
{
    // body_ = new QWidget();
    // columnLayout_ = new QHBoxLayout();
    // body_->setLayout(columnLayout_);
    //
    // mainLayout_->addWidget(body_);
    
    view_ = new QTableView();
    view_->verticalHeader()->setVisible(false);
    view_->horizontalHeader()->setVisible(false);

    QAbstractItemModel* model = new SimpleModel();
    view_->setModel(model);

    mainLayout_->addWidget(view_);
}

