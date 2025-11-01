#include "AbstractTable.h"
#include <qboxlayout.h>
#include <qevent.h>
#include <qpushbutton.h>
#include <qsplitter.h>
#include <qtableview.h>
#include <qheaderview.h>
#include <QLabel>

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

    headerSplitter_ = new TableWidgetHeaderSplitter();

    headerLayout->addWidget(headerSplitter_);

    connect(headerSplitter_, &QSplitter::splitterMoved, this, &TableWidget::onHeaderMoved);
    connect(headerSplitter_, &TableWidgetHeaderSplitter::resized, this, &TableWidget::onHeaderResized);

    for(size_t i=0; i<headerSplitter_->count(); ++i)
    {
        headerSplitter_->setCollapsible(i, false);
    }

    // headerSplitter_->installEventFilter(this);
    mainLayout_->addWidget(header_);
}

void TableWidget::onHeaderResized()
{
    auto sizes = headerSplitter_->sizes();
    int pos = 0;
    for(size_t i=0; i<headerSplitter_->count(); ++i)
    {
        pos+=sizes[i];
        onHeaderMoved(pos, i);
    }
}

void TableWidget::onHeaderMoved(int pos, int index)
{
    for(size_t i=0; i<headerSplitter_->count(); ++i)
    {
        int width = headerSplitter_->sizes()[i];
        view_->setColumnWidth(i, width);
    }
}

void TableWidget::initBody()
{
    view_ = new QTableView();
    view_->verticalHeader()->setVisible(false);
    view_->horizontalHeader()->setVisible(false);
    view_->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    mainLayout_->addWidget(view_);
}

void TableWidget::setHorizontalHeaderLabels(const QStringList &labels)
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

