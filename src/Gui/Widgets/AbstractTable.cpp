#include "AbstractTable.h"
#include <qboxlayout.h>
#include <qevent.h>
#include <qpushbutton.h>
#include <qsplitter.h>
#include <qtableview.h>
#include <qheaderview.h>
#include <QLabel>

// TODO: 
//  - Refactor code
//  - Make sure the text is fitting nicely
//  - Improve the look of the header splitters
//  - Capitalize top text
//  - Move the text to the right of the column on the header
//  - Add in icons next to each item in the list

dvWidgets::AbstractTable::AbstractTable()
{
    mainLayout_ = new QVBoxLayout(this);
    mainLayout_->setSpacing(0);
    mainLayout_->setContentsMargins(0, 0, 0, 0);

    initHeader();
    initBody();
}

void dvWidgets::AbstractTable::initHeader()
{

    header_ = new QWidget();
    header_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    header_->setProperty("class", "TableHeader");
    header_->setFixedHeight(30);

    QHBoxLayout* headerLayout = new QHBoxLayout(header_);
    headerLayout->setContentsMargins(0,0,0,0);

    headerSplitter_ = new dvWidgets::AbstractTableHeaderSplitter();
    headerSplitter_->setProperty("class", "DefaultSplitter");

    headerLayout->addWidget(headerSplitter_);

    connect(headerSplitter_, &QSplitter::splitterMoved, this, &dvWidgets::AbstractTable::onHeaderMoved);
    connect(headerSplitter_, &dvWidgets::AbstractTableHeaderSplitter::resized, this, &dvWidgets::AbstractTable::onHeaderResized);

    for(size_t i=0; i<headerSplitter_->count(); ++i)
    {
        headerSplitter_->setCollapsible(i, false);
    }

    // headerSplitter_->installEventFilter(this);
    mainLayout_->addWidget(header_);
}

void dvWidgets::AbstractTable::onHeaderResized()
{
    auto sizes = headerSplitter_->sizes();
    int pos = 0;
    for(size_t i=0; i<headerSplitter_->count(); ++i)
    {
        pos+=sizes[i];
        onHeaderMoved(pos, i);
    }
}

void dvWidgets::AbstractTable::onHeaderMoved(int pos, int index)
{
    for (size_t i=0; i<headerSplitter_->count(); ++i)
    {
        int width = headerSplitter_->sizes()[i];
        view_->setColumnWidth(i, width);
    }
}

void dvWidgets::AbstractTable::initBody()
{
    view_ = new QTableView();
    view_->setContentsMargins(10, 0, 10, 0);
    view_->verticalHeader()->setVisible(false);
    view_->horizontalHeader()->setVisible(false);
    view_->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    mainLayout_->addWidget(view_);
}

void dvWidgets::AbstractTable::setHorizontalHeaderLabels(const QStringList &labels)
{
    size_t i=0;
    for(QString label : labels)
    {
        if(i<headerSplitter_->count())
        {
            QLabel* labelWidget = static_cast<QLabel*>(headerSplitter_->widget(i));
            labelWidget->setText(label);
        }
        {
            QLabel* labelWidget = new QLabel(label);
            labelWidget->setAlignment(Qt::AlignCenter);
            headerSplitter_->addWidget(labelWidget);
        }
        ++i;
    }
}

