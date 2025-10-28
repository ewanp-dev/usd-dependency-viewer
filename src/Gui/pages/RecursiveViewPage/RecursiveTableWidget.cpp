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
#include "./TableWidget.h"

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

    model_->clear();

    size_t numDependencies = activeNode_->getNumChildren();
    std::vector<std::shared_ptr<DependencyNode>> dependencyNodes = activeNode_->getChildNodes();

    // TODO: Convert the font to a global font so we can use across the interface
    QFont itemFont = QFont("Sans Serif", 10);
    itemFont.setUnderline(true);

    model_->setRowCount(static_cast<int>(numDependencies));
    for (size_t i = 0; i < numDependencies; i++) {
        std::shared_ptr<DependencyNode> dependencyNode = dependencyNodes[i];

        QString fileName = dependencyNode->getFileName().c_str();
        QStandardItem *nameItem =  new QStandardItem(fileName);
        nameItem->setToolTip(fileName);
        nameItem->setEditable(false);
        nameItem->setForeground(QBrush(QColor(210, 186, 146)));
        nameItem->setFont(itemFont);

        QString filePath = dependencyNode->getFilePath().c_str();
        QStandardItem *pathItem = new QStandardItem(filePath);
        pathItem->setToolTip(filePath);
        pathItem->setEditable(false);

        QStandardItem *fileSizeItem = new QStandardItem(QString::number(static_cast<qulonglong>(i)));
        fileSizeItem->setEditable(false);

        QStandardItem *numChildrenItem = new QStandardItem(QString::number(dependencyNode->getNumChildren()));
        numChildrenItem->setEditable(false);

        QStandardItem *dateModifiedItem = new QStandardItem(QString::number(static_cast<qulonglong>(i)));
        dateModifiedItem->setEditable(false);

        model_->setItem(i, 0, nameItem);
        model_->setItem(i, 1, pathItem);
        model_->setItem(i, 2, numChildrenItem);
        model_->setItem(i, 3, fileSizeItem);
        model_->setItem(i, 4, dateModifiedItem);
    }
}

void RecursiveTableWidget::initTable()
{
    table_ = new TableWidget();
    model_ = new QStandardItemModel();
    table_->setModel(model_);
    // table_->setRowCount(static_cast<int>(itemDependencies_.size()));
    model_->setColumnCount(5);
    // table_->horizontalHeader()->setStretchLastSection(true);

    // NOTE: We might want to add some more columns later on down the line
    // might be worth converting table_ to its own QStringList as a variable
    table_->setHorizontalHeaderLabels({ "File Name", "File Path", "Children", "File Size", "Date Modified" });
    // table_->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::Stretch);

    connect(table_->getView(), &QTableWidget::doubleClicked, this, &RecursiveTableWidget::onCellDoubleClicked);

    mainLayout_->addWidget(table_);
}

void RecursiveTableWidget::initFooter()
{

}

void RecursiveTableWidget::onCellDoubleClicked(const QModelIndex& index)
{
    // NOTE: not the best way to get the graph nod3 but it's fine.

    int row = index.row();
    int column = index.column();

    std::cout << "double clicked\n";
    std::cout << "row: " << row << "column: " << column << "\n";
    auto tableItem = model_->item(row, 1);
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
