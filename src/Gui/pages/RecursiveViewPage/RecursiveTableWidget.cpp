#include "RecursiveTableWidget.h"
#include <QHeaderView>
#include <qboxlayout.h>
#include <QLabel>
#include <iostream>
#include <QObject>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QToolTip>
#include <qtablewidget.h>
#include <qtextedit.h>
#include "Gui/interface/AbstractButton.h"
#include <QResizeEvent>

RecursiveTableWidget::RecursiveTableWidget()
{
    mainLayout_ = new QVBoxLayout(this);
    setLayout(mainLayout_);

    setContentsMargins(0,0,0,0);

    initHeader();
    initTable();
    initFooter();
}

void RecursiveTableWidget::initHeader()
{
    header_ = new QWidget();
    header_->setContentsMargins(0,0,0,0);
    QHBoxLayout* headerLayout =  new QHBoxLayout();
    header_->setLayout(headerLayout);

    headerPathWidget_ = new QLineEdit("/");
    headerPathWidget_->setReadOnly(true);
    headerLayout->addWidget(headerPathWidget_);

    AbstractButton* navHomeButton = new AbstractButton();
    navHomeButton->setIconFromImage(":/icons/home.png");
    headerLayout->addWidget(navHomeButton);
    connect(navHomeButton, &AbstractButton::clicked, this, [this](){setActivePath(NodePath(getActivePath().getRootNode()));});

    AbstractButton* navUpButton = new AbstractButton();
    navUpButton->setIconFromImage(":/icons/nav-arrow-up.png");
    headerLayout->addWidget(navUpButton);
    connect(navUpButton, &AbstractButton::clicked, this, [this](){setActivePath(getActivePath().popNode());});

    // AbstractButton* upButton = new AbstractButton();
    // upButton->setIconFromImage(":/icons/home.png");
    // headerLayout->addWidget(upButton);

    mainLayout_->addWidget(header_);
}

const NodePath RecursiveTableWidget::getActivePath() const
{
    return nodePath_;
}

void RecursiveTableWidget::setActivePath(NodePath nodePath)
{
    nodePath_ = nodePath;
    activeNode_ = nodePath.getLeafNode();
    std::cout << "new path: " << getActivePath() << "\n";
    std::cout << "activeNode: " << activeNode_->getFilePath() << "\n";

    QString pathString;
    for(std::shared_ptr<DependencyNode> node : nodePath_)
    {
        pathString.append(" / "+node->getFileStem());
    }
    QFontMetrics metrics(headerPathWidget_->font());
    headerPathWidget_->setText(pathString);

    table_->clearContents();

    size_t numDependencies = activeNode_->getNumChildren();
    std::vector<std::shared_ptr<DependencyNode>> dependencyNodes = activeNode_->getChildNodes();

    // TODO: Convert the font to a global font so we can use across the interface
    QFont itemFont = QFont("Sans Serif", 10);
    itemFont.setUnderline(true);

    table_->setRowCount(static_cast<int>(numDependencies));
    for (size_t i = 0; i < numDependencies; i++) {
        std::shared_ptr<DependencyNode> dependencyNode = dependencyNodes[i];

        QString fileName = dependencyNode->getFileName().c_str();
        QTableWidgetItem *nameItem =  new QTableWidgetItem(fileName);
        nameItem->setToolTip(fileName);

        QString filePath = dependencyNode->getFilePath().c_str();
        QTableWidgetItem *pathItem = new QTableWidgetItem(filePath);
        pathItem->setToolTip(filePath);

        QTableWidgetItem *fileSizeItem = new QTableWidgetItem(QString::number(static_cast<qulonglong>(i)));
        QTableWidgetItem *numChildrenItem = new QTableWidgetItem(QString::number(dependencyNode->getNumChildren()));
        QTableWidgetItem *dateModifiedItem = new QTableWidgetItem(QString::number(static_cast<qulonglong>(i)));

        nameItem->setForeground(QBrush(QColor(210, 186, 146)));
        nameItem->setFont(itemFont);

        table_->setItem(i, 0, nameItem);
        table_->setItem(i, 1, pathItem);
        table_->setItem(i, 2, numChildrenItem);
        table_->setItem(i, 3, fileSizeItem);
        table_->setItem(i, 4, dateModifiedItem);
    }
}

void RecursiveTableWidget::initTable()
{
    table_ = new QTableWidget();
    table_->verticalHeader()->setVisible(false);
    // table_->setRowCount(static_cast<int>(itemDependencies_.size()));
    table_->setColumnCount(5);
    table_->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    table_->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    table_->setEditTriggers(QAbstractItemView::NoEditTriggers);
    // table_->horizontalHeader()->setStretchLastSection(true);

    // NOTE: We might want to add some more columns later on down the line
    // might be worth converting table_ to its own QStringList as a variable
    table_->setHorizontalHeaderLabels({ "File Name", "File Path", "Children", "File Size", "Date Modified" });
    // table_->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::Stretch);

    connect(table_, &QTableWidget::cellDoubleClicked, this, &RecursiveTableWidget::onCellDoubleClicked);

    mainLayout_->addWidget(table_);
}

void RecursiveTableWidget::resizeEvent(QResizeEvent *event)
{
    std::cout << "resize\n";
    std::cout << "old size: " << event->oldSize().width() << " " << event->oldSize().height() << "\n";
    std::cout << "new size: " << event->size().width() << " " << event->size().height() << "\n";
    double sizeDelta = static_cast<float>(event->size().width())/event->oldSize().width();

    auto numColumns = table_->columnCount();
    for(int i=0; i<numColumns; i++)
    {
        double newWidth = sizeDelta*table_->columnWidth(i);
        table_->setColumnWidth(i, newWidth);
    }
    std::cout<< "size delta: " << sizeDelta << "\n";

}

void RecursiveTableWidget::initFooter()
{

}

void RecursiveTableWidget::onCellDoubleClicked(int row, int column)
{
    // NOTE: not the best way to get the graph nod3 but it's fine.

    std::cout << "double clicked\n";
    std::cout << "row: " << row << "column: " << column << "\n";
    auto tableItem = table_->item(row, 1);
    if(!tableItem)
    {
        std::cout << "table item doesn't exist\n";
        return;
    }
    std::string filePath = tableItem->text().toStdString();

    std::vector<std::shared_ptr<DependencyNode>> childNodes = activeNode_->getChildNodes();
    for(auto node : childNodes)
    {
        if(node->getFilePath() == filePath)
        {
            if(node->getNumChildren()==0)
            {
                std::cout << "Node has no children\n";
                break;
            }
            std::cout << "setting active node\n";

            setActivePath(getActivePath().appendNode(node));
            break;
        }
    }
}
